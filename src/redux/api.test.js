///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2002-2021, Open Design Alliance (the "Alliance").
// All rights reserved.
//
// This software and its documentation and related materials are owned by
// the Alliance. The software may only be incorporated into application
// programs owned by members of the Alliance, subject to a signed
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable
// trade secrets of the Alliance and its suppliers. The software is also
// protected by copyright law and international treaty provisions. Application
// programs incorporating this software must include the following statement
// with their copyright notices:
//
//   This application incorporates Open Design Alliance software pursuant to a
//   license agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2021 by Open Design Alliance.
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////
const YAML = require("yamljs");
const fetchMock = require("fetch-mock");
const fs = require("fs");

const api = require("./api");
var schema = null;

function getByPath(schema, path) {
  path = parsePath(path);
  var object = schema;
  for (let i = 0; i < path.length; i++) {
    object = object[path[i]];
  }
  return object;
}

function parsePath(path) {
  path = path.replace("#/", "");
  const arr = path.split("/");
  return arr;
}

function isOptionalPath(path) {
  const regex = /{\w+}/gi;
  return regex.test(path);
}
function isPathEqual(path1, path2) {
  path1 = path1.replace(/\?[^\/]+$/g, "").replace(/\/$/g, "");
  path2 = path2.replace(/\?[^\/]+$/g, "").replace(/\/$/g, "");
  const arr1 = path1.split("/");
  const arr2 = path2.split("/");
  if (arr1.length !== arr2.length) {
    return false;
  }
  for (let i = 0; i < arr1.length; i++) {
    if (arr1[i] !== arr2[i] && !isOptionalPath(arr1[i]) && !isOptionalPath(arr2[i])) {
      return false;
    }
  }
  return true;
}

function findPath(url, schema) {
  const paths = Object.keys(schema.paths);
  const path = paths.find((path) => isPathEqual(path, url));
  if (path) {
    return schema.paths[path];
  }
  return null;
}

function applyProperties(object, properties, schema) {
  const keys = Object.keys(properties);
  keys.forEach((name) => {
    object[name] = createFrom(properties[name], schema);
  });
}
function createObject(obj, schema) {
  //{"type":"object","properties":{"id":{"type":"string"},"fileId":{"type":"string"},"data":{"description":"markup user data","type":"string"}}}
  var result = {};
  if (obj.properties) {
    applyProperties(result, obj.properties, schema);
  }
  return result;
}

function createArray(obj, schema) {
  //"{"type":"array","items":{"$ref":"#/components/schemas/Markup"}}"
  return [createFrom(obj.items, schema)];
}

function createString(obj, schema) {
  const format = obj.format;
  switch (format) {
    case "date":
      return new Date().toISOString();
    case "binary":
      return new Uint8Array([0]).buffer;
    default:
      return "string";
  }
}

function createInteger(obj, schema) {
  return 0;
}

function createBoolean(obj, schema) {
  return true;
}

function createNumber(obj, schema) {
  return obj.default || 0;
}

function createFrom(obj, schema) {
  const type = obj.type;
  if (obj["$ref"]) {
    return createFrom(getByPath(schema, obj["$ref"]), schema);
  }
  switch (type) {
    case "object":
      return createObject(obj, schema);
    case "array":
      return createArray(obj, schema);
    case "string":
      return createString(obj, schema);
    case "integer":
      return createInteger(obj, schema);
    case "boolean":
      return createBoolean(obj, schema);
    case "number":
      return createNumber(obj, schema);
    default:
      return null;
  }
}

function createResponse(obj, schema) {
  const responceSchema = obj.content[Object.keys(obj.content)[0]].schema;
  return createFrom(responceSchema, schema);
}

function mockXhrs() {
  delete global.XMLHttpRequest.prototype.response;
  delete global.XMLHttpRequest.prototype.responseText;
  delete global.XMLHttpRequest.prototype.status;

  global.XMLHttpRequest.prototype.open_ = global.XMLHttpRequest.prototype.open;
  global.XMLHttpRequest.prototype.open = function (...args) {
    this.method = args[0].toLowerCase();
    this.uri = args[1].replace(/\.?([\w\/]+\w).*/g, "$1");
    const path = findPath(this.uri, schema)[this.method];
    if (path) {
      const responses = path.responses;
      const responcesCode = Object.keys(responses);
      const status = responcesCode[0];
      const responseData = responses[status];

      this.status = status;
      this.response = createResponse(responseData, schema);
      this.responseText = JSON.stringify(this.response);

      return this.open_(...args);
    } else {
      throw new Error(`Unmatched ${this.method} to ${this.uri}`);
    }
  };
  global.XMLHttpRequest.prototype.send = function (...args) {
    const event = {
      target: this,
    };
    this.upload.onloadstart && this.upload.onloadstart(event);
    this.upload.onprogress && this.upload.onprogress(event);
    this.upload.onloadend && this.upload.onloadend(event);

    this.onloadend && this.onloadend(event);
    this.onload && this.onload(event);
    //this.onerror && this.onerror(event);
  };
}

function mockFetches() {
  const keys = Object.keys(schema.paths);
  keys.map((path) => {
    const data = schema.paths[path];

    Object.keys(data).forEach((method) => {
      let index = 0;

      fetchMock[method](
        path,
        (url, req) => {
          const responses = data[method].responses;
          const responcesCode = Object.keys(responses);
          let currentIndex = index++;

          if (currentIndex >= responcesCode.length) {
            currentIndex = 0;
          }
          const responce = responses[responcesCode[currentIndex]];
          const jsonContext = Object.keys(responce.content)[0].indexOf("json") !== -1;
          return {
            status: responcesCode[currentIndex],
            headers: { "content-type": Object.keys(responce.content)[0] },
            body: createResponse(responce, schema),
            text: JSON.stringify(createResponse(responce, schema)),
          };
        },
        {
          matcher: (url) => {
            return isPathEqual(path, url.replace(/\/$/g, ""));
          },
        }
      );
    });
  });
}

describe("API test", () => {
  beforeAll(() => {
    return new Promise((resolve, reject) => {
      const url = "https://opencloud.azureedge.net/spec/master/open_cloud_server_api.yml";
      YAML.load(url, function (schema, err) {
        if (!schema) {
          reject("Can't load schema");
        } else {
          const keys = Object.keys(schema.paths);
          console.log("Avaliable paths", keys);
          resolve(schema);
        }
      });
    })
      .then((data) => (schema = data))
      .then(() => {
        let config = fs.readFileSync("./public/config.json", {
          encoding: "utf8",
        });

        config = JSON.parse(config);
        config.api_host = ".";
        config.registration_host = ".";
        config.visualizejs_url = "./Visualize.js";

        config = JSON.stringify(config);
        fetchMock.get("./config.json", config);
        global.download = function () {};
        api.default.host = ".";
        api.default.token = "123";
        api.authAPI.host = ".";
        api.authAPI.token = "123";
      })
      .then(() => {
        mockFetches();
        mockXhrs();
      });
  });

  it("getPreviewUrl(fileId)", () => {
    return Promise.resolve(api.default.getPreviewUrl(0));
  });
  it("getDefaultPreviewUrl()", () => {
    return Promise.resolve(api.default.getDefaultPreviewUrl());
  });
  it("getFiles(page, limit)", () => {
    return api.default.getFiles(0, 16);
  });
  it("getFileById(fileId)", () => {
    return api.default.getFileById(0);
  });
  it("postFile(file, onProgress)", () => {
    //const file = new File(new Blob([new Uint8Array([0,1,2,3]).buffer]),"test.dwg")
    const file = new File(["foo"], "programmatically_created.dwg");
    return api.default.postFile(file, (progress) => {});
  });
  it("deleteFile(fileId)", () => {
    return api.default.deleteFile(0);
  });
  it("getDownload(fileId, dataId)", () => {
    return api.default.getDownload(0, 0);
  });
  it("getGeometry(fileId, cancelSignal)", () => {
    return api.default.getGeometry(0, {});
  });
  it("getProperties(fileId)", () => {
    return api.default.getProperties("000134");
  });
  it("getNativeProperties(fileId, nativeHandle)", () => {
    return api.default.getNativeProperties(0, 0);
  });
  it("postGeometryJob(fileId)", () => {
    return api.default.postGeometryJob(0);
  });
  it("postExportJob(fileId, format)", () => {
    return api.default.postExportJob(0, "vsf");
  });
  it("postPropertiesJob(fileId)", () => {
    return api.default.postPropertiesJob(0);
  });
  it("getJobs()", () => {
    return api.default.getJobs();
  });
  it("getJob(jobId)", () => {
    return api.default.getJob(0);
  });

  it("getchunk(fileId, chunk)", () => {
    return new Promise((resolve, reject) => {
      const request = api.default.getchunk(0, "chunk");
      request.onload = resolve;
      request.onerror = reject;
      request.start();
    });
  });

  it("getMarkup(fileId)", () => {
    return api.default.getMarkup(0);
  });
  it("getMarkupPreviewUrl(fileId, markupId)", () => {
    return Promise.resolve(api.default.getMarkupPreviewUrl(0, 0));
  });
  it("postMarkup(fileId, markup)", () => {
    return api.default.postMarkup(0, { data: "{}" });
  });
  it("deleteMarkup(fileId, id)", () => {
    return api.default.deleteMarkup(0, 0);
  });
  it("editMarkup(fileId, id, markup)", () => {
    return api.default.editMarkup(0, 0, { data: "{}" });
  });
  it("updatePreview(fileId, preview)", () => {
    return api.default.updatePreview(0, {});
  });
  it("login({ email, password })", () => {
    return api.default.login({ email: "email@example.com", password: "123" });
  });
  it("getVersion()", () => {
    return api.default.getVersion();
  });
});

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
function jsonTryParse(text) {
  let result = null;
  try {
    result = JSON.parse(text);
  } catch (err) {}
  return result;
}

function handleFetchError(response) {
  if (!response.ok) {
    return response.text().then((text) => {
      const message = jsonTryParse(text);
      // eslint-disable-next-line
      const error = new Error((message && message.description) || text || response.statusText);
      error.code = response.status;
      return Promise.reject(error);
    });
  }

  return response;
}

function xmlHttp(url, options) {
  const req = new XMLHttpRequest();
  req.open(options.method, url, true);

  if (options.headers) {
    for (var key in options.headers) {
      req.setRequestHeader(key, options.headers[key]);
    }
  }
  req.start = () => req.send(options.body);
  return req;
}

export class API {
  constructor() {
    this.token = null;
    this.host = null;
  }

  authXmlHttp = (url, options, progress) => {
    return new Promise((resolve, reject) => {
      const req = new XMLHttpRequest();
      req.open(options.method, this.host + url, true);
      const headers = {
        Authorization: this.token,
        "Access-Control-Allow-Origin": "*",
        ...options.headers,
      };
      req.upload.onprogress = (event) => {
        if (progress) {
          progress(event);
        }
      };
      req.upload.onloadend = (event) => {
        if (progress) {
          progress(event);
        }
      };
      req.upload.onloadstart = (event) => {
        if (progress) {
          progress(event);
        }
      };

      for (var key in headers) {
        req.setRequestHeader(key, headers[key]);
      }

      req.onloadend = (ev) => {
        let responce = jsonTryParse(ev.target.responseText) || ev.target.responseText;

        if (req.status >= 200 && req.status < 400) {
          resolve(responce);
        } else {
          // eslint-disable-next-line
          reject(new Error((responce && responce.description) || responce));
        }
      };

      req.onerror = (ev) => {
        reject(new Error(jsonTryParse(ev.target.responseText) || ev.target.responseText || "CONNECTION_REFUSED"));
      };
      req.send(options.body);
    }).catch((err) => {
      console.log(options.method, url, err.message);
      throw err;
    });
  };

  authFetch = (url, option) => {
    return fetch(this.host + url, {
      ...option,
      headers: {
        Authorization: this.token,
        "Access-Control-Allow-Origin": "*",
        ...option.headers,
      },
    })
      .then((response) => handleFetchError(response))
      .catch((err) => {
        console.log(option.method, url, err.message, err.code);
        return Promise.reject(err);
      });
  };

  getPreviewUrl(fileId) {
    return this.host + "/files/" + fileId + "/preview";
  }
  getDefaultPreviewUrl() {
    return "default-preview.png";
  }

  getFiles(page, limit) {
    var query = "";
    if (page !== undefined) {
      query += "?start=" + page;

      if (limit !== undefined) {
        query += "&limit=" + limit;
      }
    }
    return this.authFetch("/files" + query, { method: "GET" }).then((response) => response.json());
  }

  getFileById(fileId) {
    return this.authFetch("/files/" + fileId, { method: "GET" }).then((response) => response.json());
  }

  postFile(file, onProgress) {
    const data = new FormData();
    data.append("file", file);
    return this.authXmlHttp(
      "/files/",
      {
        method: "POST",
        body: data,
      },
      onProgress
    );
  }

  deleteFile(fileId) {
    return this.authFetch("/files/" + fileId, { method: "DELETE" }).then((response) => response.json());
  }

  getDownload(fileId, dataId) {
    return this.authFetch("/files/" + fileId + "/downloads/" + dataId, {
      method: "GET",
    }).then((response) => response.blob());
  }

  getGeometry(fileId, cancelSignal) {
    return this.authFetch("/files/" + fileId + "/geometry/", {
      method: "GET",
    }).then((response) => response.json());
  }

  getProperties(fileId) {
    return this.authFetch("/files/" + fileId + "/properties/", {
      method: "GET",
    }).then((response) => response.json());
  }

  getNativeProperties(fileId, nativeHandle) {
    return this.authFetch("/files/" + fileId + "/properties?handle=" + nativeHandle, { method: "GET" }).then(
      (response) => response.json()
    );
  }

  // jobs
  postGeometryJob(fileId) {
    return this.authFetch("/jobs", {
      method: "POST",
      headers: { "content-type": "application/json" },
      body: JSON.stringify({
        fileId: fileId,
        outputFormat: "geometry",
      }),
    }).then((response) => response.json());
  }
  postExportJob(fileId, format) {
    return this.authFetch("/jobs", {
      method: "POST",
      headers: { "content-type": "application/json" },
      body: JSON.stringify({
        fileId: fileId,
        outputFormat: format.toLowerCase(),
      }),
    }).then((response) => response.json());
  }
  postPropertiesJob(fileId) {
    return this.authFetch("/jobs", {
      method: "POST",
      headers: { "content-type": "application/json" },
      body: JSON.stringify({
        fileId: fileId,
        outputFormat: "properties",
      }),
    }).then((response) => response.json());
  }

  getJobs() {
    return this.authFetch("/jobs/", { method: "GET" }).then((response) => response.json());
  }
  getJob(jobId) {
    return this.authFetch("/jobs/" + jobId, { method: "GET" }).then((response) => response.json());
  }

  getchunk(fileId, chunk) {
    const options = {
      method: "GET",
      headers: {
        Authorization: this.token,
        "Access-Control-Allow-Origin": "*",
      },
    };
    const req = xmlHttp(this.host + "/files/" + fileId + "/downloads/" + chunk, options);
    req.responseType = "arraybuffer";
    return req;
  }

  getMarkup(fileId) {
    return this.authFetch(`/files/${fileId}/markup`, { method: "GET" }).then((response) => response.json());
  }

  getMarkupPreviewUrl(fileId, markupId) {
    return this.host + "/markup/preview/" + fileId + "/" + markupId;
  }

  postMarkupPreview(fileId, markupId, preview) {
    return this.authFetch("/markup/preview/" + fileId + "/" + markupId, {
      method: "POST",
      body: new Blob([preview]),
    });
  }

  postMarkup(fileId, markup) {
    return new Promise((resolve, reject) => {
      this.authFetch(`/files/${fileId}/markup`, {
        method: "POST",
        body: JSON.stringify(markup),
      })
        .then((response) => resolve(response.json()))
        .catch((err) => reject(err));
    });
  }

  deleteMarkup(fileId, id) {
    return this.authFetch(`/files/${fileId}/markup/${id}`, {
      method: "DELETE",
    }).then((response) => response.json());
  }

  editMarkup(fileId, id, markup) {
    return this.authFetch(`/files/${fileId}/markup/${id}`, {
      method: "POST",
      body: JSON.stringify(markup),
      headers: {
        "Content-Type": "application/json",
        Accept: "application/json, text/plain, */*",
      },
    }).then((response) => response.json()); //todo: must be PUT
  }

  updatePreview(fileId, preview) {
    return this.authFetch(`/files/${fileId}`, {
      method: "PUT",
      body: JSON.stringify({ preview: preview }),
      headers: {
        "Content-Type": "application/json",
        Accept: "application/json, text/plain, */*",
      },
    }).then((response) => response.json());
  }

  login({ email, password }) {
    const token = email + ":" + password;
    const hash = btoa(token);
    return this.authFetch("/token", {
      method: "GET",
      headers: { Authorization: "Basic " + hash },
    }).then((responce) => responce.json());
  }

  getVersion() {
    return this.authFetch("/version", { method: "GET" }).then((responce) => responce.json());
  }
}

export const authAPI = {
  token: "token",
  host: "http://localhost",
  authFetch: function (url, option) {
    return fetch(this.host + url, {
      ...option,
      headers: {
        Authorization: this.token,
        "Access-Control-Allow-Origin": "*",
        "Content-Type": "application/json",
        ...option.headers,
      },
    })
      .catch((err) => {
        throw new Error("Failed to fetch data from Registration server");
      })
      .then((response) => handleFetchError(response))
      .catch((err) => {
        console.log(option.method, url, err);
        throw err;
      });
  },
  register: function ({ username, email, password }) {
    const json = JSON.stringify({ username, email, password });
    return this.authFetch("/register", { method: "POST", body: json }).then((responce) => responce.json());
  },
};

const instance = new API();

export default instance;

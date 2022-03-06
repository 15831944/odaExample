import { Component } from "react";

import Window from "../../components/Window";

import ClientFactory from "../../ClientFactory";

import "antd/dist/antd.css";
import { Form, Button, Select, InputNumber, Space, Col, Row, Skeleton, Alert } from "antd";

const windowStyle = {
  left: "calc(50% - 300px)",
  top: "calc(50% - 265px)",
  width: "402px",
  height: "450px",
  maxHeight: "450px",
  maxWidth: "402px",
};

const inputStyle = {
  width: "130px",
};
const inputRotation = {
  width: "90px",
};
const inputRotationAngle = {
  width: "120px",
};

const WindowTitle = "Transform";

const composingMatrixFromTransform = (translate, rotate, scale, modelCenter, matrix) => {
  const translateMatrix = matrix.setTranslation([translate.x, translate.y, translate.z]);

  const rotateMatrix = matrix.setToRotation(rotate.angle, [rotate.x, rotate.y, rotate.z], modelCenter);

  const scaleMatrix = matrix.setToScaling(scale, modelCenter);
  return translateMatrix.postMultBy(rotateMatrix).postMultBy(scaleMatrix);
};

export class AssemblyTransformComponent extends Component {
  state = {
    models: [],

    translate: { x: 0.0, y: 0.0, z: 0.0 },
    scale: 0.0,
    rotate: { x: 0.0, y: 0.0, z: 0.0, angle: 0.0 },
    isLoading: true,
    isApplyProcess: false,
    isError: false,
    errorMessage: "",
  };

  selectedIndex = 0;

  async componentDidMount() {
    try {
      this.setState({ isLoading: true });
      const assembly = this.props.assembly;

      const viewer = this.props.viewer.visViewer();
      const modelList = [];
      let index = 0;
      for (const modelItr = viewer.getModelIterator(); !modelItr.done(); modelItr.step()) {
        const model = modelItr.getModel();
        if (model.getName()[0] !== "$") {
          const file = await ClientFactory.get().getFile(assembly.files[index]);
          index++;

          const transform = assembly.getModelTransformMatrix(model.getDatabaseHandle()) || {
            translate: { x: 0.0, y: 0.0, z: 0.0 },
            scale: 1.0,
            rotation: { x: 0.0, y: 0.0, z: 1.0, angle: 0.0 },
          };

          modelList.push({
            name: file.name,
            object: model,
            transform: transform,
          });
        }
      }

      this.setState({ models: modelList, isLoading: false });
      this.onChange(0);
    } catch (err) {
      this.setState({
        isError: true,
        errorMessage: "Cannot load transform data from server",
      });
    }
  }

  componentWillUnmount() {
    const viewer = this.props.viewer.visViewer();
    if (viewer && this.selectionSet) {
      viewer.activeView.highlightAll(this.selectionSet, false);
      this.selectionSet.delete();
    }
  }

  onChange = (index) => {
    this.selectedIndex = index;

    const viewer = this.props.viewer.visViewer();
    if (this.selectionSet) {
      viewer.activeView.highlightAll(this.selectionSet, false);
      this.selectionSet.delete();
    }

    this.selectionSet = viewer.activeView.selectCrossing([0, 9999, 9999, 0], this.state.models[index].object);

    viewer.activeView.highlightAll(this.selectionSet, true);

    const transform = this.state.models[index].transform;

    this.setState({
      translate: transform.translate,
      rotate: transform.rotation,
      scale: transform.scale,
    });
  };

  onApply = async () => {
    const uiModel = this.state.models[this.selectedIndex];
    const model = uiModel.object;

    const lib = this.props.viewer.visLib();

    const extents = model.getExtents();
    const newMatrix = composingMatrixFromTransform(
      this.state.translate,
      this.state.rotate,
      this.state.scale,
      extents.center(),
      new lib.Matrix3d()
    );

    model.setModelingMatrix(newMatrix, true);

    const assembly = this.props.assembly;
    try {
      this.setState({ isApplyProcess: true });
      await assembly.setModelTransformMatrix(model.getDatabaseHandle(), {
        translate: this.state.translate,
        rotation: this.state.rotate,
        scale: this.state.scale,
      });

      this.state.models[this.selectedIndex].transform = {
        translate: this.state.translate,
        rotation: this.state.rotate,
        scale: this.state.scale,
      };
    } catch (error) {
      this.setState({
        isError: true,
        errorMessage: "Cannot apply transform for model",
      });
    } finally {
      this.setState({ isApplyProcess: false, isError: false });
    }
  };

  onResetToDefault = () => {
    this.setState({
      translate: { x: 0.0, y: 0.0, z: 0.0 },
      scale: 1.0,
      rotate: { x: 0.0, y: 0.0, z: 1.0, angle: 0.0 },
    });
  };

  render() {
    const modelListTemplate = this.state.models.map((value, index) => {
      return (
        <Select.Option key={index} value={index}>
          {value.name}
        </Select.Option>
      );
    });

    const { translate, rotate, scale, isApplyProcess, isLoading, isError, errorMessage } = this.state;

    const uiTransform = (
      <div>
        <Form layout="vertical" size="middle">
          <Form.Item label="Choose model for transformation">
            <Select defaultValue={0} onChange={this.onChange}>
              {modelListTemplate}
            </Select>
          </Form.Item>
          <Form.Item label="Translation">
            <InputNumber
              style={inputStyle}
              addonBefore="X:"
              decimalSeparator="."
              value={translate.x}
              step={0.1}
              onChange={(value) => this.setState({ translate: { ...translate, x: value } })}
            />

            <InputNumber
              style={inputStyle}
              addonBefore="Y:"
              decimalSeparator="."
              value={translate.y}
              step={0.1}
              onChange={(value) => this.setState({ translate: { ...translate, y: value } })}
            />

            <InputNumber
              style={inputStyle}
              addonBefore="Z:"
              decimalSeparator="."
              value={translate.z}
              step={0.1}
              onChange={(value) => this.setState({ translate: { ...translate, z: value } })}
            />
          </Form.Item>
        </Form>

        <Form layout="vertical">
          <Form.Item label="Rotation">
            <InputNumber
              addonBefore="X:"
              style={inputRotation}
              decimalSeparator="."
              value={rotate.x}
              step={0.1}
              max={1.0}
              min={-1.0}
              onChange={(value) => this.setState({ rotate: { ...rotate, x: value } })}
            />

            <InputNumber
              addonBefore="Y:"
              style={inputRotation}
              decimalSeparator="."
              value={rotate.y}
              step={0.1}
              max={1.0}
              min={-1.0}
              onChange={(value) => this.setState({ rotate: { ...rotate, y: value } })}
            />

            <InputNumber
              addonBefore="Z:"
              style={inputRotation}
              decimalSeparator="."
              value={rotate.z}
              step={0.1}
              max={1.0}
              min={-1.0}
              onChange={(value) => this.setState({ rotate: { ...rotate, z: value } })}
            />

            <InputNumber
              addonBefore="Angle:"
              style={inputRotationAngle}
              decimalSeparator="."
              value={(rotate.angle * (180 / Math.PI)).toFixed(2)}
              step={0.1}
              min={0.0}
              max={360.0}
              onChange={(value) =>
                this.setState({
                  rotate: { ...rotate, angle: value * (Math.PI / 180) },
                })
              }
            />
          </Form.Item>
          <Form.Item label="Scale">
            <InputNumber
              style={inputRotation}
              decimalSeparator="."
              value={scale}
              step={0.1}
              min={0.1}
              onChange={(value) => this.setState({ scale: value })}
            />
          </Form.Item>
        </Form>

        <Form layout="inline" size="large">
          <Row>
            <Col span={48}>
              <Space style={{ width: "100%" }}>
                <Button type="primary" loading={isApplyProcess} onClick={this.onApply}>
                  Apply changes
                </Button>
                <Button loading={isApplyProcess} onClick={this.onResetToDefault}>
                  Reset to default
                </Button>
              </Space>
            </Col>
          </Row>
        </Form>
      </div>
    );

    const uiLoading = (
      <div>
        <Skeleton active />
        <Skeleton active />
      </div>
    );

    return (
      <Window className="properties-explorer" title={WindowTitle} style={windowStyle} onClose={this.props.onClose}>
        {isLoading ? uiLoading : uiTransform}
        {isError ? (
          <Alert
            style={{
              position: "absolute",
              top: "56px",
              zIndex: "1",
              left: "0px",
              width: "100%",
            }}
            message="Error"
            description={errorMessage}
            type="error"
            onClose={() => this.setState({ isError: false })}
            closable
          />
        ) : null}
      </Window>
    );
  }
}

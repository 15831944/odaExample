import React from "react";
import "./style.css";

export function VisualizeProgress(props) {
  const { value } = props;
  const strokeOffset = 440 - (440 * value) / 100;
  return (
    <div className="vjs-progress">
      <div className="vjs-progress__percent">
        <svg className="vjs-progress__svg">
          <circle className="vjs-progress__circle" cx="70" cy="70" r="70"></circle>
          <circle
            className="vjs-progress__circle"
            cx="70"
            cy="70"
            r="70"
            style={{ strokeDashoffset: `${strokeOffset}` }}
          ></circle>
        </svg>
        <div className="vjs-progress__num">
          <div className="vjs-progress__h2">
            {value}
            <span className="vjs-progress__span">%</span>
          </div>
        </div>
      </div>
      <div className="vjs-progress__text">VisualizeJS downloading...</div>
    </div>
  );
}

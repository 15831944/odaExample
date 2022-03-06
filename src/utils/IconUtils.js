export const MaterialIcon = (iconName, sizeParam) => {
  const size = sizeParam || 30;
  return () => {
    return (
      <span className="material-icons" style={{ verticalAlign: "baseline", fontSize: `${size}px` }}>
        {iconName}
      </span>
    );
  };
};

export const SvgIcon = (url, widthParam, heightParam) => {
  const width = widthParam || 30;
  const height = heightParam || 30;
  return () => {
    return (
      <img
        src={url}
        alt=""
        style={{
          verticalAlign: "baseline",
          width: `${width}px`,
          height: `${height}px`,
        }}
      ></img>
    );
  };
};

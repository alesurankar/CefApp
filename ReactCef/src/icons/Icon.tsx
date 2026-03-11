import React from "react";
import { ICON_PATHS } from "./IconPaths";
import type { IconName } from "./IconPaths";

type Props = {
  name: IconName;
  size?: number;
  color?: string;
  strokeWidth?: number;
};

const Icon: React.FC<Props> = ({
  name,
  size = 24,
  color = "currentColor",
  strokeWidth = 1.5,
}) => {
  const path = ICON_PATHS[name];

  return (
    <svg
      width={size}
      height={size}
      viewBox="0 0 24 24"
      fill="none"
      stroke={color}
      strokeWidth={strokeWidth}
      strokeLinecap="round"
      strokeLinejoin="round"
    >
      <path d={path} />
    </svg>
  );
};

export default Icon;
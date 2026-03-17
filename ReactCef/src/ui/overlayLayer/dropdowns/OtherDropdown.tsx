import BaseDropdown from "./BaseDropdown";


interface OtherDropdownProps {
  x: number;
  y: number;
}

const OtherDropdown = ({ x, y }: OtherDropdownProps) => {
  return (
    <BaseDropdown x={x} y={y}>
      <div>
        <div>This is Other Dropdown</div>
      </div>
    </BaseDropdown>
  );
};

export default OtherDropdown;
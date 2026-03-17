import BaseDropdown from "./BaseDropdown";


interface ViewPanelDropdownProps {
  x: number;
  y: number;
}

const ViewPanelDropdown: React.FC<ViewPanelDropdownProps> = ({ x, y }) => {
  return (
    <BaseDropdown x={x} y={y}>
      <div>
        <div>This is View Panel Dropdown</div>
        <div>Second line</div>
      </div>
    </BaseDropdown>
  );
};

export default ViewPanelDropdown;
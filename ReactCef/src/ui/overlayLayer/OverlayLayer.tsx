import BaseDropdown from "./dropdowns/BaseDropdown";


interface DropdownState {
  visible: boolean;
  x: number;
  y: number;
}
interface OverlayLayerProps {
  dropdown: DropdownState;
  hideDropdown: () => void;
}

const OverlayLayer: React.FC<OverlayLayerProps> = ({dropdown, hideDropdown}) => {

  return (
    <div
      className={`fixed top-0 left-0 w-full h-full z-50 ${
        dropdown.visible ? "pointer-events-auto" : "pointer-events-none"
      }`}
      onMouseDown={hideDropdown}
    >{dropdown.visible && <BaseDropdown x={dropdown.x} y={dropdown.y}/>}
    </div>
  );
};

export default OverlayLayer;
import ViewPanelDropdown from "./dropdowns/ViewPanelDropdown";
import OtherDropdown from "./dropdowns/OtherDropdown";


interface DropdownState {
  x: number;
  y: number;
  visible: boolean;
  type?: "viewPanel" | "other"
}
interface OverlayLayerProps {
  dropdown: DropdownState;
  hideDropdown: () => void;
}

const OverlayLayer = ({ dropdown, hideDropdown }: OverlayLayerProps) => {
  
  const renderDropdown = () => {
    if (!dropdown.visible) return null;

    switch (dropdown.type) {
      case "viewPanel":
        return <ViewPanelDropdown x={dropdown.x} y={dropdown.y} />;
      case "other":
        return <OtherDropdown x={dropdown.x} y={dropdown.y}/>;
      default:
        return null;
    }
  };
  
  return (
    <div
      className={`fixed inset-0 z-50 ${
        dropdown.visible ? "pointer-events-auto" : "pointer-events-none"
      }`}
      onMouseDown={hideDropdown}
    >{renderDropdown()}
    </div>
  );
};

export default OverlayLayer;
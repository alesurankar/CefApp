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

const OverlayLayer = ({dropdown, hideDropdown}: OverlayLayerProps) => {
  if (!dropdown.visible) return null;
  
  const renderDropdown = () => {
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
      className="fixed top-0 left-0 w-full h-full z-50 auto"
      onMouseDown={hideDropdown}
    >{renderDropdown()}
    </div>
  );
};

export default OverlayLayer;
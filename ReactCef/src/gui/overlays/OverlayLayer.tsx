import DropdownWindow from "../dropdown/DropdownWindow";


interface DropdownState {
  visible: boolean;
  x: number;
  y: number;
}
interface OverlayLayerProps {
  dropdown: DropdownState;
}

const OverlayLayer: React.FC<OverlayLayerProps> = ({dropdown}) => {

  return (
    <div className="fixed top-0 left-0 w-full h-full pointer-events-none z-50">
      {dropdown.visible && <DropdownWindow x={dropdown.x} y={dropdown.y}/>}
    </div>
  );
};

export default OverlayLayer;
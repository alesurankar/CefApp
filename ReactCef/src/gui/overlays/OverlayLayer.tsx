import DropdownWindow from "../dropdown/DropdownWindow";


const OverlayLayer = () => {
  const showDropdown = true;
  const x = 50;
  const y = 50;

  return (
    <div className="fixed top-0 left-0 w-full h-full pointer-events-none z-50">
      {showDropdown && <DropdownWindow x={x} y={y}/>}
    </div>
  );
};

export default OverlayLayer;
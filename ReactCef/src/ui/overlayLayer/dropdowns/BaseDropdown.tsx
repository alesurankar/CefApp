
interface BaseDropdownProps {
  x: number;
  y: number;
}

const BaseDropdown: React.FC<BaseDropdownProps> = ({ x, y }) => {
  return (
    <div
      className="pointer-events-auto absolute bg-gray-800 text-white p-3 rounded shadow-lg"
      style={{ top: y, left: x }}
    >
      <div>This is Dropdown Window</div>
      <br />
      <div>Second Line</div>
    </div>
  );
};

export default BaseDropdown;
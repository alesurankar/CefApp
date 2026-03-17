
interface BaseDropdownProps {
  x: number;
  y: number;
  children: React.ReactNode;
}

const BaseDropdown: React.FC<BaseDropdownProps> = ({ x, y, children }) => {

  return (
    <div
      className="pointer-events-auto absolute bg-gray-800 text-white p-3 rounded shadow-lg"
      style={{ top: y, left: x }}
    >{children}
    </div>
  );
};

export default BaseDropdown;
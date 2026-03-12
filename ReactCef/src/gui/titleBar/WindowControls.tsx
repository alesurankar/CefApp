import { myCefMinimize, myCefResize, myCefClose } from "../../cef/cefInterface.ts"


const WindowControls = () => {
  return (
    <div className="flex h-full">
      {/* space for dragbar */}
      <div className="w-12 h-8 flex items-center justify-center"></div>
      {/* buttons */}
      <button
        title="Minimize"
        className="w-12 h-full flex items-center justify-center hover:bg-[#373737]"
        onClick={myCefMinimize}
      >―
      </button>
      <button
        title="Resize"
        className="w-12 h-full flex items-center justify-center hover:bg-[#373737]"
        onClick={myCefResize}
      >☐
      </button>
      <button
        title="Close"
        className="w-12 h-full flex items-center justify-center hover:bg-red-600"
        onClick={myCefClose}
      >✕
      </button>
    </div>
  );
};

export default WindowControls;
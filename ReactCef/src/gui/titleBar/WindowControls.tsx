import { myCefMinimize, myCefResize, myCefClose } from "../../cef/cefInterface.ts"


const WindowControls = () => {
  return (
    <div className="flex h-full">
      <button
        className="w-12 h-full flex items-center justify-center hover:bg-[#373737]"
        onClick={myCefMinimize}
      >―
      </button>
      <button
        className="w-12 h-full flex items-center justify-center hover:bg-[#373737]"
        onClick={myCefResize}
      >☐
      </button>
      <button
        className="w-12 h-full flex items-center justify-center hover:bg-red-600"
        onClick={myCefClose}
      >✕
      </button>
    </div>
  );
};

export default WindowControls;
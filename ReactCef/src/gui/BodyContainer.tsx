import { myCefCreateD3DWindow } from "../cef/cefInterface.ts"


interface BodyContainerProps {
  spawnTab: () => void;
}

const BodyContainer: React.FC<BodyContainerProps> = ({ spawnTab }) => {

  return (
    <div className="flex flex-1 overflow-auto">
      {/* Left Navigation Bar */}
      <div className="w-12 bg-[#373737] text-[#a8a8a8] flex flex-col items-center">
        <button 
          className="w-12 h-12 hover:text-[#ffffff] hover:font-bold"
          onClick={spawnTab}
          >Tab
        </button>
        <button 
          className="w-12 h-12 hover:text-[#ffffff] hover:font-bold"
          onClick={myCefCreateD3DWindow}
        >Wnd
        </button>
      </div>

      {/* Main Frames Area */}
      <div className="flex-1">

      </div>
    </div>
  );
};

export default BodyContainer;

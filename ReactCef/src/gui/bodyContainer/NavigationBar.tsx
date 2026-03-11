import { myCefCreateD3DWindow } from "../../cef/cefInterface.ts"


interface NavigationBarProps {
  spawnTab: () => void;
}

const NavigationBar: React.FC<NavigationBarProps> = ({ spawnTab }) => {
  return (
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
  );
};

export default NavigationBar;
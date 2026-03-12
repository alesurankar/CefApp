import { myCefCreateD3DWindow } from "../../cef/cefInterface.ts"
import Icon from "../../icons/Icon.tsx";


interface NavigationBarProps {
  spawnTab: () => void;
}

const NavigationBar: React.FC<NavigationBarProps> = ({ spawnTab }) => {
  return (
    <div className="w-12 bg-[#373737] text-[#a8a8a8] flex flex-col items-center">
      <button 
        title="New Tab"
        className="w-12 h-12 flex items-center justify-center hover:text-[#ffffff] hover:font-bold"
        onClick={spawnTab}
      ><Icon name="plus" size={24}/>
      </button>

      <button 
        title="D3DWindow"
        className="w-12 h-12 flex items-center justify-center hover:text-[#ffffff] hover:font-bold"
        onClick={myCefCreateD3DWindow}
      ><Icon name="tv" size={24}/>
      </button>
    </div>
  );
};

export default NavigationBar;
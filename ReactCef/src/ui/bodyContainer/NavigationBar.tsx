import { myCefCreateD3DWindow } from "../../cef/cefInterface.ts"
import Icon from "../icons/Icon.tsx";


interface NavigationBarProps {
  spawnView: () => void;
  className?: string;
}

const NavigationBar: React.FC<NavigationBarProps> = ({ spawnView, className }) => {
  return (
    <div className={`flex-col bg-[#373737] text-[#a8a8a8] ${className}`}>
      <button 
        title="New Tab"
        className="h-12 flex items-center justify-center hover:text-[#ffffff] hover:font-bold"
        onClick={spawnView}
      ><Icon name="plus" size={26}/>
      </button>

      <button 
        title="D3DWindow"
        className="h-12 flex items-center justify-center hover:text-[#ffffff] hover:font-bold"
        onClick={myCefCreateD3DWindow}
      ><Icon name="tv" size={26}/>
      </button>
    </div>
  );
};

export default NavigationBar;
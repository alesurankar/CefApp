import Icon from "../icons/Icon.tsx";


interface NavigationBarProps {
  spawnView: (type: "empty" | "D3DWindow") => void;
  className?: string;
}

const NavigationBar = ({ spawnView, className }: NavigationBarProps) => {
  return (
    <div className={`flex-col bg-[#373737] text-[#a8a8a8] ${className}`}>
      <button 
        title="EmptyFrame"
        className="h-12 flex items-center justify-center hover:text-[#ffffff] hover:font-bold"
        onClick={() => (spawnView("empty"))}
      ><Icon name="plus" size={26}/>
      </button>

      <button 
        title="D3DWindow"
        className="h-12 flex items-center justify-center hover:text-[#ffffff] hover:font-bold"
        onClick={() => (spawnView("D3DWindow"))}
      ><Icon name="tv" size={26}/>
      </button>
    </div>
  );
};

export default NavigationBar;
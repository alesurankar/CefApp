import TabContainer from "./TabContainer.tsx";
import WindowControls from "./WindowControls.tsx";
import Icon from "../../icons/Icon.tsx";


interface Tab {
  id: number;
  title: string;
}
interface TitleBarProps {
  tabs: Tab[];
  closeTab: (id: number) => void;
}

const TitleBar: React.FC<TitleBarProps> = ({ tabs, closeTab }) => {

  return (
    <div className="h-8 w-full flex items-center justify-between bg-[#202020] text-white select-none">
      <div className="flex items-center flex-1 overflow-hidden">
        {/* Navigation Toggle Button */}
        <div className="flex-shrink-0 w-12 h-8">
          <button
            title="Properties"
            className="w-full h-full flex items-center justify-center hover:bg-[#373737] text-[#a8a8a8]"
            // onClick={showProps}
          ><Icon name="bars_arrow_down" size={20}/>
          </button>
        </div>
        {/* Scrollable tabs */}
        <div className="flex-1 overflow-x-auto">
          <TabContainer tabs={tabs} closeTab={closeTab} />
        </div>
      </div>
      <WindowControls />
    </div>
  );
};

export default TitleBar;

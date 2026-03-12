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
          ><Icon name="bars_arrow_down" size={20}/>
          </button>
        </div>
        <TabContainer tabs={tabs} closeTab={closeTab}/>
      </div>
      <WindowControls />
    </div>
  );
};

export default TitleBar;

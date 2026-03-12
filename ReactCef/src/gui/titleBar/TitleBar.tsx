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
      {/* Navigation Toggle Button */}
      <button
        title="Properties"
        className="w-12 h-full flex items-center justify-center hover:bg-[#373737] text-[#a8a8a8]"
      ><Icon name="bars_arrow_down" size={20}/>
      </button>
      <TabContainer tabs={tabs} closeTab={closeTab}/>
      <WindowControls />
    </div>
  );
};

export default TitleBar;

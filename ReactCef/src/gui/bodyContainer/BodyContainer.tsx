import NavigationBar from "./NavigationBar.tsx";
import MainFrameArea from "./MainFrameArea.tsx";


interface Tab {
  id: number;
  title: string;
}
interface BodyContainerProps {
  tabs: Tab[];
  spawnTab: () => void;
}

const BodyContainer: React.FC<BodyContainerProps> = ({ tabs, spawnTab }) => {

  return (
    <div className="flex flex-1 overflow-auto">
      <NavigationBar spawnTab={spawnTab}/>
      <MainFrameArea tabs={tabs}/>
    </div>
  );
};

export default BodyContainer;

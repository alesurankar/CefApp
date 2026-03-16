import BaseFrame from "./frames/BaseFrame";


interface Tab {
  id: number;
  title: string;
}
interface MainFrameAreaProps {
  tabs: Tab[]
}

const MainFrameArea: React.FC<MainFrameAreaProps> = ({ tabs }) => {
  return (
    <div className="flex-1">
      {tabs.map(tab => (
        <BaseFrame
          key={tab.id}
          title={tab.title}
        />
      ))}
    </div>
  );
};

export default MainFrameArea;
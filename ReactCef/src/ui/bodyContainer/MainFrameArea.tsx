import BaseFrame from "./frames/BaseFrame";


interface View {
  id: number;
  title: string;
  type?: string;
}
interface MainFrameAreaProps {
  views: View[]
  activeViewId: number | null;
}

const MainFrameArea: React.FC<MainFrameAreaProps> = ({ views, activeViewId }) => {
  return (
    <div className="flex-1">
      {views.map(view => (
        <BaseFrame
          key={view.id}
          title={view.title}
          visible={view.id === activeViewId}
        />
      ))}
    </div>
  );
};

export default MainFrameArea;
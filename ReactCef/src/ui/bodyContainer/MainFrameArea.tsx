import BaseFrame from "./frames/BaseFrame";


interface View {
  id: number;
  title: string;
}
interface MainFrameAreaProps {
  views: View[]
}

const MainFrameArea: React.FC<MainFrameAreaProps> = ({ views }) => {
  return (
    <div className="flex-1">
      {views.map(view => (
        <BaseFrame
          key={view.id}
          title={view.title}
        />
      ))}
    </div>
  );
};

export default MainFrameArea;
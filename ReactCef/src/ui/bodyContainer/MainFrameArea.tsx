import BaseFrame from "./frames/BaseFrame";


interface View {
  id: number;
  title: string;
  type?: string;
}
interface MainFrameAreaProps {
  views: View[]
  activeViewId: number | null;
  className?: string;
}

const MainFrameArea = ({ views, activeViewId, className }: MainFrameAreaProps) => {
  return (
    <div className={`${className}`}>
      {views.length === 0 && (
        <div className="flex flex-1 items-center justify-center text-gray-500 text-lg">
          Welcome! Open a new view.
        </div>
      )}
      
      {views.map(view => (
        <BaseFrame
          key={view.id}
          title={view.title}
          visible={view.id === activeViewId}
          className="flex flex-1"
        />
      ))}
    </div>
  );
};

export default MainFrameArea;
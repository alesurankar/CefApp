import EmptyFrame from "./frames/EmptyFrame";
import D3DFrame from "./frames/D3DFrame";
import type { View } from "../../types/view";


interface MainFrameAreaProps {
  views: View[]
  activeViewId: number | null;
  className?: string;
}

const MainFrameArea = ({ views, activeViewId, className }: MainFrameAreaProps) => {
  const activeView = views.find(v => v.id === activeViewId) ?? views[0];

  const renderActiveFrame = () => {
    if (!activeView) return null;

    switch (activeView.kind) {
      case "d3d": return <D3DFrame key={activeView.id} visible className="flex flex-1" />;
      case "empty":
      default: return <EmptyFrame key={activeView.id} visible className="flex flex-1" />;
    }
  };

  return (
    <div className={className}>
      {views.length === 0 && (
        <div className="flex flex-1 items-center justify-center text-gray-500 text-lg">
          Welcome! Open a new view.
        </div>
      )}
      {renderActiveFrame()}
    </div>
  );
};

export default MainFrameArea;
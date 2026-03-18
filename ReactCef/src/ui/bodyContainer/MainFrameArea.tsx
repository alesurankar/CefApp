import EmptyFrame from "./frames/EmptyFrame";
import D3DFrame from "./frames/D3DFrame";
import type { View } from "../../types/view";


interface MainFrameAreaProps {
  views: View[]
  activeViewId: number | null;
  className?: string;
}

const MainFrameArea = ({ views, activeViewId, className }: MainFrameAreaProps) => {
  
  return (
    <div className={className}>
      {views.length === 0 && (
        <div className="flex flex-1 items-center justify-center text-gray-500 text-lg">
          Welcome! Open a new view.
        </div>
      )}
      
      {views.map((view) => {
      const isActive = view.id === activeViewId;

      switch (view.kind) {
        case "d3d":
          return (
            <D3DFrame
              key={view.id}
              visible={isActive}
              className="flex flex-1"
            />
          );

        case "empty":
        default:
          return (
            <EmptyFrame
              key={view.id}
              visible={isActive}
              className="flex flex-1"
            />
          );
        }
      })}
    </div>
  );
};

export default MainFrameArea;
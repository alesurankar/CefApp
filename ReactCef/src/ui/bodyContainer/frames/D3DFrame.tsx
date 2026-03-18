// import { myCefCreateD3DWindow } from "../../cef/cefInterface.ts"
import BaseFrame from "./BaseFrame.tsx";


interface D3DFrameProps {
  visible: boolean;
  className: string;
}

const D3DFrame = ({ visible, className }: D3DFrameProps) => {
  return (
    <BaseFrame title="D3DWindow" visible={visible} className={className}>
      <div>
        {/* TODO: call this function: myCefCreateD3DWindow */}
      </div>
    </BaseFrame>
  );
};

export default D3DFrame;
import { myCefCreateD3DWindow } from "../../../cef/cefInterface.ts";
import { myCefDestroyD3DWindow } from "../../../cef/cefInterface.ts";
import { useEffect } from "react";
import BaseFrame from "./BaseFrame.tsx";


interface D3DFrameProps {
  visible: boolean;
  className: string;
}

const D3DFrame = ({ visible, className }: D3DFrameProps) => {
  useEffect(() => {
    if (!visible) return;
    myCefCreateD3DWindow();
    
    return () => {
      myCefDestroyD3DWindow();
    };
  }, [visible]);

  return (
    <BaseFrame title="D3DWindow" visible={visible} className={className}>
      <div>
      </div>
    </BaseFrame>
  );
};

export default D3DFrame;
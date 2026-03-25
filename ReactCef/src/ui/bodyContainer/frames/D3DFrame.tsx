import { myCefCreateD3DRenderer } from "../../../cef/cefInterface.ts";
import { myCefDestroyD3DRenderer } from "../../../cef/cefInterface.ts";
import { useEffect } from "react";
import BaseFrame from "./BaseFrame.tsx";


interface D3DFrameProps {
  visible: boolean;
  className: string;
}

const D3DFrame = ({ visible, className }: D3DFrameProps) => {
  useEffect(() => {
    if (!visible) return;
    myCefCreateD3DRenderer();
    
    return () => {
      myCefDestroyD3DRenderer();
    };
  }, [visible]);

  return (
    <BaseFrame title="D3DRenderer" visible={visible} className={className}>
      <div>
      </div>
    </BaseFrame>
  );
};

export default D3DFrame;
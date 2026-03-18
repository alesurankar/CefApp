import BaseFrame from "./BaseFrame";


interface EmptyFrameProps {
  visible: boolean;
  className: string;
}

const EmptyFrame = ({ visible, className }: EmptyFrameProps) => {
  return (
    <BaseFrame title="EmptyFrame" visible={visible} className={className}>
      <div>EmptyFrame</div>
    </BaseFrame>
  );
};

export default EmptyFrame;
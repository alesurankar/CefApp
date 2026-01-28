interface ModalProps {
  onClose?: () => void;
  children?: React.ReactNode;
  maxWidth?: string;
  padding?: string;
}

const Modal = ({ onClose, children, maxWidth = "max-w-3xl", padding = "p-0" }: ModalProps) => (
    <div className="fixed inset-0 z-50 flex items-center justify-center bg-black bg-opacity-50">
      <div className={`relative bg-white rounded-lg w-full ${maxWidth} ${padding}`}>
        {/* Close button */}
        <button
          className={`absolute top-1 right-3 text-xl font-bold`}
          onClick={onClose}
        >
          ✕
        </button>

        {/* Modal content */}
        {children}
      </div>
    </div>
  );


export default Modal;

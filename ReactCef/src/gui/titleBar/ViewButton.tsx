import Icon from "../../icons/Icon.tsx";


interface ViewButtonProps {
  onClick: (e: React.MouseEvent) => void;
}

const ViewButton: React.FC<ViewButtonProps> = ({ onClick }) => {

  return (
    <div className="flex-shrink-0 w-12 h-8">
      <button
        title="View Panel"
        className="w-full h-full flex items-center justify-center hover:bg-[#373737] text-[#a8a8a8]"
        onClick={onClick}
      ><Icon name="bars_arrow_down" size={20}/>
      </button>
    </div>
  );
};

export default ViewButton;
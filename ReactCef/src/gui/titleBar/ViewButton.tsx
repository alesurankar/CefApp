import Icon from "../../icons/Icon.tsx";


const ViewButton = () => {
  const showProps = () => {

  }

  return (
    <div className="flex-shrink-0 w-12 h-8">
      <button
        title="Properties"
        className="w-full h-full flex items-center justify-center hover:bg-[#373737] text-[#a8a8a8]"
        onClick={showProps}
      ><Icon name="bars_arrow_down" size={20}/>
      </button>
    </div>
  );
};

export default ViewButton;
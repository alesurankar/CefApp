const TitleBar = () => {
  return (
    <div id="titlebar"
        className="h-8 w-full flex items-center justify-between bg-gray-900 text-white select-none [webkit-app-region:drag]"
    >

      {/* Left empty for spacing if needed */}
      <div className="pl-2"></div>

      {/* Window controls */}
      <div className="flex space-x-2 pr-11">
        <button id="minimize"
          className="w-6 h-6 flex items-center justify-center hover:bg-gray-700 rounded-sm [webkit-app-region:no-drag]"
        >
          _
        </button>
        <button id="maximize"
          className="w-6 h-6 flex items-center justify-center hover:bg-gray-700 rounded-sm [webkit-app-region:no-drag]"
        >
          ☐
        </button>
        <button id="close"
          className="w-6 h-6 flex items-center justify-center hover:bg-red-600 rounded-sm [webkit-app-region:no-drag]"
        >
          X
        </button>
      </div>
    </div>
  );
};

export default TitleBar;

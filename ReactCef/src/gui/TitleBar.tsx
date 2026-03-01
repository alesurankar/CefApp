interface CefApi {
    CloseFunc(): void;
    MinimizeFunc(): void;
    ResizeFunc(): void;
}
const cef = window as unknown as CefApi;

function myCefClose(): void
{
    return cef.CloseFunc();
}

function myCefMinimize(): void
{
    return cef.MinimizeFunc();
}

function myCefResize(): void
{
    return cef.ResizeFunc();
}

const TitleBar = () => {
  return (
    <div id="titlebar"
      className="h-8 w-full flex items-center justify-between bg-[#202020] text-white select-none"
    >
      <div className="flex-1 h-8 bg-[#373737]">
        Custom Title Bar
      </div>

      {/* Window controls */}
      <div className="flex">
        <button
          className="w-12 h-8 flex items-center justify-center hover:bg-[#373737]"
          onClick={myCefMinimize}
        >
          ―
        </button>
        <button
          className="w-12 h-8 flex items-center justify-center hover:bg-[#373737]"
          onClick={myCefResize}
        >
          ☐
        </button>
        <button
          className="w-12 h-8 flex items-center justify-center hover:bg-red-600"
          onClick={myCefClose}
        >
          ✕
        </button>
      </div>
    </div>
  );
};

export default TitleBar;

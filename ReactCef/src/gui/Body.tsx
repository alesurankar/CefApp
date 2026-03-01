import { useState } from "react";

interface CefApi {
    OverlayWindowFunc(): void;
    SetHandleXFunc(x: number): void;
}
const cef = window as unknown as CefApi;

function myCefOverlayWindow(): void
{
    cef.OverlayWindowFunc();
}

function myCefSetHandleX(x: number): void
{
    const clamped = Math.max(0, Math.min(1000, x));
    cef.SetHandleXFunc(clamped);
}

interface BodyFrameProps {
    className?: string;
}

const Body: React.FC<BodyFrameProps> = ({ className }) => {
  const [handleX, setHandleX] = useState(0);
  return (
    <div className={`bg-gray-800 text-white p-4 ${className ?? ''}`}>
      <div>
        <button className="
          w-12 h-10 
          bg-[#111111] text-white 
          border border-gray-700
          rounded
          transition-colors duration-80 ease-in-out
          hover:bg-[#333333]
          active:bg-[#555555]"
        onClick={myCefOverlayWindow}
        >
        ☐
        </button>
        <input
            type="number"
            className="w-20 h-10 bg-[#111111] rounded border border-gray-700 text-white px-2"
            value={handleX}
            onChange={(e) => setHandleX(parseInt(e.target.value, 10))}
            min={0}
            max={1000}
        />
        <button
          className="w-12 h-10 bg-[#111111] rounded border border-gray-700 hover:bg-[#333333] active:bg-[#555555]"
          onClick={() => myCefSetHandleX(handleX)}
        >
          Set X
        </button>
      </div>
      <div className="text-4xl font-bold text-center my-20">
        <p className="text-red-500">React Frontend</p>
        <br /><br /><br />
        <p>Body</p>
        </div>
    </div>
  );
};

export default Body;

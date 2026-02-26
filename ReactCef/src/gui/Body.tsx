
interface CefApi {
    OverlayWindowFunc(): void;
}
const cef = window as unknown as CefApi;

function myCefOverlayWindow(): void
{
    return cef.OverlayWindowFunc();
}

interface BodyFrameProps {
  className?: string;
}

const Body: React.FC<BodyFrameProps> = ({ className }) => {

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
        onClick={() => myCefOverlayWindow()}
        >
        ☐
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

import { myCefCreateD3DWindow, myCefSpawnTabWindow } from "../cef/cefInterface.ts"


interface BodyFrameProps {
  className?: string;
  spawnTab: () => void;
}

const BodyFrame: React.FC<BodyFrameProps> = ({ className, spawnTab }) => {

  return (
    <div className={`bg-gray-800 text-white p-4 ${className ?? ''}`}>
      <div>
        <button
          className="w-28 h-16 bg-[#111111] rounded border border-gray-700 hover:bg-[#333333] active:bg-[#555555]"
          onClick={spawnTab}
        >Spawn Tab
        </button>
      </div>
      <div>
        <button className="w-12 h-10 bg-[#111111] text-white border border-gray-700 rounded 
          transition-colors duration-80 ease-in-out hover:bg-[#333333] active:bg-[#555555]"
        onClick={myCefCreateD3DWindow}
        >☐
        </button>
        <button
          className="w-28 h-16 bg-[#111111] rounded border border-gray-700 hover:bg-[#333333] active:bg-[#555555]"
          onClick={() => myCefSpawnTabWindow()}
        >Spawn Tab
        </button>
      </div>
      <div className="text-4xl font-bold text-center my-20">
        <p className="text-red-500">React Frontend</p>
        <br /><br /><br />
        <p>BodyFrame</p>
        <h1 className="text-blue-300">this is title1</h1>
        <h1>this is title1</h1>
        <h2>this is title2</h2>
        <h3>this is title3</h3>
        <h4>this is title4</h4>
        <h5>this is title5</h5>
        <h6>this is title6</h6>
        <p>this is p container</p>
        </div>
    </div>
  );
};

export default BodyFrame;

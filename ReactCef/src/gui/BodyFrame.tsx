import { useState } from "react";


interface CefApi {
    function1(
        text: string,
        accept: (result: boolean) => void,
        reject: (msg: string) => void
    ): void;
    function2(): void;
    function3(
        text: string,
        accept: (result: boolean) => void,
        reject: (msg: string) => void
    ): void;
}
const cef = window as unknown as CefApi;

function myCefFunction1(text: string): Promise<boolean> 
{
    return new Promise((resolve, reject) =>
        cef.function1(text, resolve, reject)
    );
}

function myCefFunction2(): void
{
    return cef.function2();
}

function myCefFunction3(text: string): Promise<boolean> {
    return new Promise((resolve, reject) =>
        cef.function3(text, resolve, reject)
    );
}


interface BodyFrameProps {
  className?: string;
}

const BodyFrame: React.FC<BodyFrameProps> = ({ className }) => {
    const [answer, setAnswer] = useState<string | null>(null);
    const [inProgress, setInProgress] = useState(false);

    async function handleClick() 
    {
        setInProgress(true);
        setAnswer(null);
        try {
            if (await myCefFunction1("Path 1")) {
                if (await myCefFunction1("Path 2")) {
                    if (await myCefFunction3("")) {
                        setAnswer("3");
                    } 
                    else {
                        setAnswer("3.1");
                    }
                } 
                else {
                    setAnswer((await myCefFunction1("Path 2.1")) ? "2.1" : "2");
                }
            } 
            else {
                setAnswer((await myCefFunction1("Path 1.1")) ? "1.1" : "1");
            }
        } 
        finally {
            setInProgress(false);
        }
    }

  return (
    <div className={`bg-gray-900 text-white p-4 ${className ?? ''}`}>
      <div className="text-4xl font-bold text-center my-20">
        <p>
            {inProgress ? "Test in progress..." : answer ?? "NO DATA"}
        </p>
            <button
                className="text-red-500 mt-6" onClick={handleClick}>Async function
            </button>
            <button onClick={() => myCefFunction2()}>Sync function</button>
        </div>
    </div>
  );
};

export default BodyFrame;

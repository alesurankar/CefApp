import { useState } from "react";

interface CefApi {
    function1(
        text: string,
        accept: (result: boolean) => void,
        reject: (msg: string) => void
    ): void;
}
const cef = window as unknown as CefApi;

function myCefFunction(text: string): Promise<boolean> {
    return new Promise((resolve, reject) =>
        cef.function1(text, resolve, reject)
    );
}

const Page1 = () => {
    const [answer, setAnswer] = useState<string | null>(null);
    const [inProgress, setInProgress] = useState(false);

    async function handleClick() 
    {
        setInProgress(true);
        setAnswer(null);
        try {
            if (await myCefFunction("Path 1")) {
                if (await myCefFunction("Path 2")) {
                    if (await myCefFunction("Path 3")) {
                        setAnswer("3");
                    } 
                    else {
                        setAnswer("3.1");
                    }
                } 
                else {
                    setAnswer((await myCefFunction("Path 2.1")) ? "2.1" : "2");
                }
            } 
            else {
                setAnswer((await myCefFunction("Path 1.1")) ? "1.1" : "1");
            }
        } 
        finally {
            setInProgress(false);
        }
    }

    return (
        <div className="text-4xl font-bold text-center my-20">
        <p>
            {inProgress
            ? "Test in progress..."
            : answer ?? "NO DATA"}
        </p>
            <button
                className="text-red-500 mt-6"
                onClick={handleClick}
            >
                JUST DO IT
            </button>
        </div>
    );
};
export default Page1;
import Button from "../../utils/Button";

interface CefApi {
    CloseFunc(): void;
    MinimizeFunc(): void;
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

const Page2 = () => {
    return (
        <div className="text-4xl font-bold text-center my-20">
            <Button type="button" title="Close Browser" onClick={() => myCefClose()}/>
            <Button type="button" title="Minimize Window" onClick={() => myCefMinimize()}/>
        </div>
    )
}

export default Page2;
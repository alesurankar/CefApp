import Button from "../../utils/Button";

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

const Page2 = () => {
    return (
        <div className="text-4xl font-bold text-center my-20">
            <Button type="button" title="Close Browser" onClick={() => myCefClose()}/>
            <Button type="button" title="Minimize Window" onClick={() => myCefMinimize()}/>
            <Button type="button" title="Resize Window" onClick={() => myCefResize()}/>
        </div>
    )
}

export default Page2;
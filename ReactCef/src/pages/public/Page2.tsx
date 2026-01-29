import Button from "../../utils/Button";

interface CefApi {
    function4(): void;
}
const cef = window as unknown as CefApi;

function myCefFunction4(): void
{
    return cef.function4();
}

const Page2 = () => {
    return (
        <div className="text-4xl font-bold text-center my-20">
            <Button type="button" title="Close Browser" onClick={() => myCefFunction4()}/>
        </div>
    )
}

export default Page2;
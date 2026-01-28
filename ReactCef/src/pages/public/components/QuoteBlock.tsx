import { useState } from "react"
import { BlackNinja } from '../../../assets/images/images'
import { QuoteIcon } from '../../../assets/icons/icons'
import api from '../../../utils/api'
import Button from '../../../utils/Button'

interface QuoteBlockProps {
  image?: string;
  text: string;
  author?: string;
}

interface QuoteInProps {
  onCommentAdded: () => void;
}

const QuoteBlock = ({image = BlackNinja,text,author = "Anonymous"}: QuoteBlockProps) => {
  return (
        <section className="relative w-full bg-gray-400 p-6 lg:p-12 flex flex-col lg:flex-row border-t border-black"> 
            <div className="shrink-0 w-24 lg:w-40 lg:-mt-6">
                <img src={image} alt='ninja' className='w-full object-contain'/>
            </div>
            <div>
                <div className="shrink-0 lg:mx-6 w-8 lg:w-14">
                    <img src={QuoteIcon} alt='Quote' className='w-full h-full'/>
                </div>
                <div className="flex-1 min-w-0 mt-1 lg:-mt-10 lg:ml-24">
                    <p className="text-md lg:text-lg text-black break-all">{text}</p>
                    <p className="mt-2 lg:mr-12 text-right text-lg lg:text-xl text-black font-bold">{author}</p>
                </div>
            </div>
        </section>     
    )
}

const QuoteIn = ({ onCommentAdded }: QuoteInProps) => {
    const [comment, setComment] = useState("");
    const [loading, setLoading] = useState(false);

   const submitComment = async () => {
        if (!comment.trim()) return alert("Comment cannot be empty!");

        setLoading(true);
        try {
            const response = await api.post("/comments", { text: comment });
            //console.log("Comment created:", response.data.comment);
            //alert("Comment submitted!");
            setComment("");
            onCommentAdded();
        } catch (err: any) {
            console.error("API error:", err.response?.data || err.message);
            alert("Failed to submit comment");
        } finally {
            setLoading(false);
        }
    };

    return (
        <section className="bg-gray-400 ">
            {/* Left side */}
            <div className="pt-4 pl-4">
                <div className="pb-8">
                    <Button
                        title='Submit'
                        mainClassName='bg-[#4a5748] hover:bg-[#283227ff]'
                        titleClassName='text-xl text-white'
                        onClick={submitComment}
                    /> 
                </div>
            </div> 
            {/* Right side */}
            <div className="lg:-mt-24 lg:ml-80 pb-10 lg:pr-10">
                <div >
                    <textarea 
                    value={comment}
                    onChange={(e) => setComment(e.target.value)}
                    placeholder="write your thing here..." 
                    className="w-full border border-gray-300 rounded-md px-3 py-2 text-md lg:text-lg focus:outline-none focus:ring-2 focus:ring-black"
                    />
                </div>
            </div>
        </section>
    )
}

export {
    QuoteBlock,
    QuoteIn,
} 
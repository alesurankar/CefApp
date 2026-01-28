import { Weapon1, Weapon2, Weapon3, Weapon4 } from '../../../assets/images/images';

interface Weapon {
    icon: any;           
    title: string;       
    description: string; 
    className?: string;  
}

const Weapons = () => {
    const RenderWeapon = (props: Weapon) => {
        return (
            <div className={`${props.className} flex flex-col items-center justify-center`}>
                {/* Weapon Icon Container */}
                <div className='shrink-0 w-24 h-24'>
                    <img
                        className='w-full h-full'
                        src={props.icon}
                        alt='Weapon Icon'
                    />
                </div>
                
                {/* Feature Title */}
                <h3 className='text-2xl font-bold text-textColor text-center mt-6'>{props.title}</h3>
                
                {/* Feature Description */}
                <p className='text-lg text-textColor text-center opacity-80 mt-2'>{props.description}</p>
            </div>
        );
    }

    return (
        <section className='w-screen bg-whiteColor px-8 py-20 lg:p-24 flex flex-col lg:flex-row items-center justify-center lg:justify-between'>
            {/* Weapon1: Katana */}
            <RenderWeapon
                className='lg:w-56'
                icon={Weapon1}
                title={`Katana`}
                description={`sharp blades.`}
            />
            
            {/* Weapon2: Kusarifundo */}
            <RenderWeapon
                className='my-10 lg:my-0 lg:w-56'
                icon={Weapon2}
                title={`Kusarifundo`}
                description={`surprise weapon.`}
            />
            
            {/* Weapon3: Bo */}
            <RenderWeapon
                className='lg:w-56'
                icon={Weapon3}
                title={`Bo`}
                description={`long reach.`}
            />
            
            {/* Weapon4: Shuriken */}
            <RenderWeapon
                className='mt-10 lg:mt-0 lg:w-56'
                icon={Weapon4}
                title={`Shuriken`}
                description={`distance attack.`}
            />
        </section>
    )
}

export default Weapons
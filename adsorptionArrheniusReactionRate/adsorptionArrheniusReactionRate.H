/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2019 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::adsorptionArrheniusReactionRate

Description
    A modified Arrhenius reaction rate that calculates the reaction rate, and including the
	consertration of empty adsorption cites (M):

        k = (A * T^beta * exp(-Ta/T))*a*M

    Where a is the surface area per unit volume, the name of which is
    specified by the user.
	M is calculated, from the user defined adsorption maximum (adsMax [mg/Kg]) and 
	the user given adsorbed specie, as [Maximum]-[Adsorbed].

SourceFiles
    adsorptionArrheniusReactionRateI.H

	adsorptionArrheniusReactionRate.H

\*---------------------------------------------------------------------------*/

#ifndef adsorptionArrheniusReactionRate_H
#define adsorptionArrheniusReactionRate_H

#include "ArrheniusReactionRate.H"
#include "volFields.H"
#include "scalarField.H"
#include "typeInfo.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of friend functions and operators

class adsorptionArrheniusReactionRate;

Ostream& operator<<(Ostream&, const adsorptionArrheniusReactionRate&);

/*---------------------------------------------------------------------------*\
             Class adsorptionArrheniusReactionRate Declaration
\*---------------------------------------------------------------------------*/

class adsorptionArrheniusReactionRate
:
    public ArrheniusReactionRate
{
    // Private Data
		
        //- Name of the surface area per unit volume field
        const word aName_;

        //- The surface area per unit volume field
        const scalarField& aField_;
		
		//- Adsorption capacity
		const scalar adsMax_;
		
		//- Name of adsorbed specie
		const word adsoName_;
		
		//- The surface area per unit volume field
        const scalarField& adsoField_;
		
		//- Name of adsorbent specie
		const word adsorbentName_;
		
		//- The surface area per unit volume field
        const scalarField& adsorbentField_;


		
public:

    // Constructors

        //- Construct from dictionary
        inline adsorptionArrheniusReactionRate
        (
            const speciesTable& species,
            const objectRegistry& ob,
            const dictionary& dict
        );


    // Member Functions

        //- Return the type name
        static word type()
        {
            return "adsorptionArrhenius";
        }

        //- Evaluate the rate
        inline scalar operator()
        (
            const scalar p,
            const scalar T,
            const scalarField& c,
            const label li
        ) const;

        //- Evaluate the derivative
        inline scalar ddT
        (
            const scalar p,
            const scalar T,
            const scalarField& c,
            const label li
        ) const;

        //- Write to stream
        inline void write(Ostream& os) const;


    // Ostream Operator

        inline friend Ostream& operator<<
        (
            Ostream&,
            const adsorptionArrheniusReactionRate&
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "adsorptionArrheniusReactionRateI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

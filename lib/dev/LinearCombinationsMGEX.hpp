#pragma ident "$Id$"

/**
 * @file LinearCombinationsMGEX.hpp
 * This class defines handy linear combinations of GDS data.
 */

#ifndef GPSTK_LINEARCOMBINATIONSMGEX_HPP
#define GPSTK_LINEARCOMBINATIONSMGEX_HPP

//============================================================================
//
//  This file is part of GPSTk, the GPS Toolkit.
//
//  The GPSTk is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 2.1 of the License, or
//  any later version.
//
//  The GPSTk is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with GPSTk; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
//
//  Dagoberto Salazar - gAGE ( http://www.gage.es ). 2007, 2008, 2009
//
//============================================================================
//  
//  Revision
//
//  2014/02/24  Add p2Prefit and l2Prefit 
//  2014/03/20  Add c1MinusIono, p1MinusIono, p2MinusIono
//
//  2014/06/17  Add pcCorrection/lcCorrection/p1Correction/l1Correction/
//                  pdeltaCorrection/ldeltaCorrection.
//              Modified from the previous version.
//
//============================================================================



#include "DataStructures.hpp"
#include "GNSSconstants.hpp"



namespace gpstk
{

      /** @addtogroup DataStructures */
      //@{


      /** This class defines handy linear combinations of GDS data.
       *
       * This class is meant to be used with the GNSS data structures (GDS)
       * objects found in "DataStructures" class, and it is intended to be
       * coupled with class ComputeLinear.hpp.
       *
       * A typical way to use this class follows:
       *
       * @code
       *
       *      // Define a LinearCombinationsMGEX object
       *   LinearCombinationsMGEX comb;
       *
       *      // Object to compute linear combinations of data
       *      // Linear combinations will be computed in a FIFO basis
       *   ComputeLinear linear;
       *
       *      // Add a linear combination to compute PC combination using C1
       *   linear.addLinear(comb.pcCombWithC1);
       *
       *      // Add a linear combination to compute prefit residual using PC
       *   linear.addLinear(comb.pcPrefit);
       *
       *
       *      // Load observation data
       *   RinexObsStream rin("ebre0300.02o");
       *
       *      // Loads precise ephemeris object with file data
       *   SP3EphemerisStore SP3EphList;
       *   SP3EphList.loadFile("igs11513.sp3");
       *
       *      // Sets nominal position of receiver
       *   Position nominalPos(4833520.3800, 41536.8300, 4147461.2800);
       *
       *      // Declare a MOPSTropModel object, setting the defaults
       *   MOPSTropModel mopsTM( nominalPos.getAltitude(),
       *                         nominalPos.getGeodeticLatitude(), 30);
       *
       *      // Object to compute the tropospheric data
       *   ComputeTropModel computeTropo(mopsTM);
       *
       *      // Declare a basic modeler
       *   BasicModel basic(nominalPos, SP3EphList);
       *
       *   gnssRinex gRin;
       *
       *   while(rin >> gRin)
       *   {
       *
       *      gRin >> basic >> computeTropo >> linear;
       *
       *         // Dump results
       *      gRin.body.dump(cout,1);
       *
       *   }
       *
       * @endcode
       *
       * @sa ComputeLinear.hpp
       */
   class LinearCombinationsMGEX
   {
   public:

         /// Default constructor
      LinearCombinationsMGEX();


         /// Definition to compute MIC1 (c1 with minus ionospehric delays)
      gnssLinearCombination q1CombWithC1;

         /// Definition to compute MIP1
      gnssLinearCombination q1Combination;

      gnssLinearCombination q1CombinationGPS;

			/// Definition to compute MIC1 for Galileo
      gnssLinearCombination q1CombinationGalileo;

         /// Definition to compute MIP2 using C1 
      gnssLinearCombination q2CombWithC1;

         /// Definition to compute MIP2
      gnssLinearCombination q2Combination;

      gnssLinearCombination q2CombinationGPS;

			/// Definition to compute MIC5 of Galileo
      gnssLinearCombination q5CombinationGalileo;


         /// Definition to compute prefit residual of C1
      gnssLinearCombination c1Prefit;

         /// Definition to compute prefit residual of P1
      gnssLinearCombination p1Prefit;

         /// Definition to compute prefit residual of P2
      gnssLinearCombination p2Prefit;

         /// Definition to compute prefit residual of L1
      gnssLinearCombination l1Prefit;

         /// Definition to compute prefit residual of L2
      gnssLinearCombination l2Prefit;

         /// Definition to compute PC combination
      gnssLinearCombination pcCombination;

      gnssLinearCombination pcCombinationGPS;
      gnssLinearCombination pcCombinationGalileo;

         /// Definition to compute PC combination, using C1 instead of P1
      gnssLinearCombination pcCombWithC1;

         /// Definition to compute prefit residual of PC
      gnssLinearCombination pcPrefit;

      gnssLinearCombination pcPrefitGPS;
      gnssLinearCombination pcPrefitGalileo;

         /// Definition to compute prefit residual of PC
      gnssLinearCombination pcPrefitC;

         /// Definition to compute prefit residual of LC for clock estimation
      gnssLinearCombination lcPrefitC;

         /// Definition to compute LC combination
      gnssLinearCombination lcCombination;

      gnssLinearCombination lcCombinationGPS;
      gnssLinearCombination lcCombinationGalileo;

         /// Definition to compute prefit residual of LC
      gnssLinearCombination lcPrefit;

      gnssLinearCombination lcPrefitGPS;
      gnssLinearCombination lcPrefitGalileo;

         /// Definition to compute PI combination
      gnssLinearCombination piCombination;

         /// Definition to compute PI combination, using C1 instead of P1
      gnssLinearCombination piCombWithC1;

         /// Definition to compute LI combination
      gnssLinearCombination liCombination;

      gnssLinearCombination liCombinationGPS;
      gnssLinearCombination liCombinationGalileo;

         /// Definition to compute Pdelta (PW) combination
      gnssLinearCombination pdeltaCombination;
				
      gnssLinearCombination pdeltaCombinationGPS;
      gnssLinearCombination pdeltaCombinationGalileo;

         /// Definition to compute Pdelta (PW) combination, using C1 instead
         /// of P1
      gnssLinearCombination pdeltaCombWithC1;

         /// Definition to compute prefit residual of Pdelta(PW)
      gnssLinearCombination pdeltaPrefit;

         /// Definition to compute Ldelta (LW) combination
      gnssLinearCombination ldeltaCombination;

      gnssLinearCombination ldeltaCombinationGPS;
      gnssLinearCombination ldeltaCombinationGalileo;

         /// Definition to compute prefit residual of Ldelta (LW) 
      gnssLinearCombination ldeltaPrefit;

         /// Definition to compute the Melbourne-Wubbena (W) combination
      gnssLinearCombination mwubbenaCombination;

      gnssLinearCombination mwubbenaCombinationGPS;
      gnssLinearCombination mwubbenaCombinationGalileo;

         /// Definition to compute the prefit residual of Melbourne-Wubbena (W) 
         /// combination
      gnssLinearCombination mwubbenaPrefit;

         /// Definition to compute the Melbourne-Wubbena (W) combination,
         /// using C1 instead of P1
      gnssLinearCombination mwubbenaCombWithC1;

         /// Definition to compute the GRoup And PHase Ionospheric
         /// Combination (GRAPHIC) in the L1 frequency
      gnssLinearCombination GRAPHIC1Combination;

         /// Definition to compute the GRoup And PHase Ionospheric
         /// Combination (GRAPHIC) in the L1 frequency (using C1 instead of P1)
      gnssLinearCombination GRAPHIC1CombinationWithC1;

         /// Definition to compute the GRoup And PHase Ionospheric
         /// Combination (GRAPHIC) in the L2 frequency
      gnssLinearCombination GRAPHIC2Combination;

         /// Definition to compute the GRoup And PHase Ionospheric
         /// Combination (GRAPHIC) in the L5 frequency
      gnssLinearCombination GRAPHIC5Combination;

         /// Definition to compute the GRoup And PHase Ionospheric
         /// Combination (GRAPHIC) in the L6 frequency
      gnssLinearCombination GRAPHIC6Combination;

         /// Definition to compute the GRoup And PHase Ionospheric
         /// Combination (GRAPHIC) in the L7 frequency
      gnssLinearCombination GRAPHIC7Combination;

         /// Definition to compute the GRoup And PHase Ionospheric
         /// Combination (GRAPHIC) in the L8 frequency
      gnssLinearCombination GRAPHIC8Combination;

         /// Definition to compute the WL combination 
      gnssLinearCombination wlCombination;
      
         /// Definition to compute prefit residual of WL
      gnssLinearCombination wlPrefit;

      /// Definition to compute the WL2 combination
      gnssLinearCombination wl2Combination;

      /// Definition to compute prefit residual of WL2
      gnssLinearCombination wl2Prefit;

         /// Definition to compute the WL4 combination
      gnssLinearCombination wl4Combination;

         /// Definition to compute prefit residual of WL4
      gnssLinearCombination wl4Prefit;
   
   public:
      
         /// Return the frequency of the combination in cycles: i * L1 + j * L2 
      static double freqOfLC(int i, int j, double f1 = L1_FREQ_GPS, double f2 = L2_FREQ_GPS);
      
         /// Return the wavelength of the combination in cycles: i * L1 + j * L2 
      static double wavelengthOfLC(int i, int j, double f1 = L1_FREQ_GPS, double f2 = L2_FREQ_GPS);
      
         /// Return the f1 factor of the combination in cycles: i * L1 + j * L2 
      static double firstFactorOfLC(int i, int j, double f1 = L1_FREQ_GPS, double f2 = L2_FREQ_GPS);
      
         /// Return the f2 factor of the combination in cycles: i * L1 + j * L2 
      static double secondFactorOfLC(int i, int j, double f1 = L1_FREQ_GPS, double f2 = L2_FREQ_GPS); 

   }; // End of class 'LinearCombinationsMGEX'

      //@}

}
#endif // GPSTK_LINEARCOMBINATIONS_HPP

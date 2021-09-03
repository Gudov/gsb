//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Copyright (c) 2018 NVIDIA Corporation. All rights reserved.

// This file was generated by NvParameterized/scripts/GenParameterized.pl


#include "EmitterDebugRenderParams_0p0.h"
#include <string.h>
#include <stdlib.h>

using namespace NvParameterized;

namespace nvidia
{
namespace parameterized
{

using namespace EmitterDebugRenderParams_0p0NS;

const char* const EmitterDebugRenderParams_0p0Factory::vptr =
    NvParameterized::getVptr<EmitterDebugRenderParams_0p0, EmitterDebugRenderParams_0p0::ClassAlignment>();

const uint32_t NumParamDefs = 20;
static NvParameterized::DefinitionImpl* ParamDefTable; // now allocated in buildTree [NumParamDefs];


static const size_t ParamLookupChildrenTable[] =
{
	1, 8, 15, 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14, 16, 17, 18, 19,
};

#define TENUM(type) nvidia::##type
#define CHILDREN(index) &ParamLookupChildrenTable[index]
static const NvParameterized::ParamLookupNode ParamLookupTable[NumParamDefs] =
{
	{ TYPE_STRUCT, false, 0, CHILDREN(0), 3 },
	{ TYPE_STRUCT, false, (size_t)(&((ParametersStruct*)0)->apexEmitterParameters), CHILDREN(3), 6 }, // apexEmitterParameters
	{ TYPE_BOOL, false, (size_t)(&((ApexEmitterParameters_Type*)0)->VISUALIZE_APEX_EMITTER_ACTOR), NULL, 0 }, // apexEmitterParameters.VISUALIZE_APEX_EMITTER_ACTOR
	{ TYPE_BOOL, false, (size_t)(&((ApexEmitterParameters_Type*)0)->VISUALIZE_TOTAL_INJECTED_AABB), NULL, 0 }, // apexEmitterParameters.VISUALIZE_TOTAL_INJECTED_AABB
	{ TYPE_BOOL, false, (size_t)(&((ApexEmitterParameters_Type*)0)->VISUALIZE_APEX_EMITTER_ACTOR_POSE), NULL, 0 }, // apexEmitterParameters.VISUALIZE_APEX_EMITTER_ACTOR_POSE
	{ TYPE_F32, false, (size_t)(&((ApexEmitterParameters_Type*)0)->THRESHOLD_DISTANCE_APEX_EMITTER_ACTOR_POSE), NULL, 0 }, // apexEmitterParameters.THRESHOLD_DISTANCE_APEX_EMITTER_ACTOR_POSE
	{ TYPE_BOOL, false, (size_t)(&((ApexEmitterParameters_Type*)0)->VISUALIZE_APEX_EMITTER_ACTOR_NAME), NULL, 0 }, // apexEmitterParameters.VISUALIZE_APEX_EMITTER_ACTOR_NAME
	{ TYPE_F32, false, (size_t)(&((ApexEmitterParameters_Type*)0)->THRESHOLD_DISTANCE_APEX_EMITTER_ACTOR_NAME), NULL, 0 }, // apexEmitterParameters.THRESHOLD_DISTANCE_APEX_EMITTER_ACTOR_NAME
	{ TYPE_STRUCT, false, (size_t)(&((ParametersStruct*)0)->groundEmitterParameters), CHILDREN(9), 6 }, // groundEmitterParameters
	{ TYPE_BOOL, false, (size_t)(&((GroundEmitterParameters_Type*)0)->VISUALIZE_GROUND_EMITTER_ACTOR), NULL, 0 }, // groundEmitterParameters.VISUALIZE_GROUND_EMITTER_ACTOR
	{ TYPE_BOOL, false, (size_t)(&((GroundEmitterParameters_Type*)0)->VISUALIZE_GROUND_EMITTER_SPHERE), NULL, 0 }, // groundEmitterParameters.VISUALIZE_GROUND_EMITTER_SPHERE
	{ TYPE_BOOL, false, (size_t)(&((GroundEmitterParameters_Type*)0)->VISUALIZE_GROUND_EMITTER_GRID), NULL, 0 }, // groundEmitterParameters.VISUALIZE_GROUND_EMITTER_GRID
	{ TYPE_BOOL, false, (size_t)(&((GroundEmitterParameters_Type*)0)->VISUALIZE_GROUND_EMITTER_RAYCAST), NULL, 0 }, // groundEmitterParameters.VISUALIZE_GROUND_EMITTER_RAYCAST
	{ TYPE_BOOL, false, (size_t)(&((GroundEmitterParameters_Type*)0)->VISUALIZE_GROUND_EMITTER_ACTOR_POSE), NULL, 0 }, // groundEmitterParameters.VISUALIZE_GROUND_EMITTER_ACTOR_POSE
	{ TYPE_BOOL, false, (size_t)(&((GroundEmitterParameters_Type*)0)->VISUALIZE_GROUND_EMITTER_ACTOR_NAME), NULL, 0 }, // groundEmitterParameters.VISUALIZE_GROUND_EMITTER_ACTOR_NAME
	{ TYPE_STRUCT, false, (size_t)(&((ParametersStruct*)0)->impactEmitterParameters), CHILDREN(15), 4 }, // impactEmitterParameters
	{ TYPE_BOOL, false, (size_t)(&((ImpactEmitterParameters_Type*)0)->VISUALIZE_IMPACT_EMITTER_ACTOR), NULL, 0 }, // impactEmitterParameters.VISUALIZE_IMPACT_EMITTER_ACTOR
	{ TYPE_BOOL, false, (size_t)(&((ImpactEmitterParameters_Type*)0)->VISUALIZE_IMPACT_EMITTER_RAYCAST), NULL, 0 }, // impactEmitterParameters.VISUALIZE_IMPACT_EMITTER_RAYCAST
	{ TYPE_BOOL, false, (size_t)(&((ImpactEmitterParameters_Type*)0)->VISUALIZE_IMPACT_EMITTER_ACTOR_NAME), NULL, 0 }, // impactEmitterParameters.VISUALIZE_IMPACT_EMITTER_ACTOR_NAME
	{ TYPE_F32, false, (size_t)(&((ImpactEmitterParameters_Type*)0)->THRESHOLD_DISTANCE_IMPACT_EMITTER_ACTOR_NAME), NULL, 0 }, // impactEmitterParameters.THRESHOLD_DISTANCE_IMPACT_EMITTER_ACTOR_NAME
};


bool EmitterDebugRenderParams_0p0::mBuiltFlag = false;
NvParameterized::MutexType EmitterDebugRenderParams_0p0::mBuiltFlagMutex;

EmitterDebugRenderParams_0p0::EmitterDebugRenderParams_0p0(NvParameterized::Traits* traits, void* buf, int32_t* refCount) :
	NvParameters(traits, buf, refCount)
{
	//mParameterizedTraits->registerFactory(className(), &EmitterDebugRenderParams_0p0FactoryInst);

	if (!buf) //Do not init data if it is inplace-deserialized
	{
		initDynamicArrays();
		initStrings();
		initReferences();
		initDefaults();
	}
}

EmitterDebugRenderParams_0p0::~EmitterDebugRenderParams_0p0()
{
	freeStrings();
	freeReferences();
	freeDynamicArrays();
}

void EmitterDebugRenderParams_0p0::destroy()
{
	// We cache these fields here to avoid overwrite in destructor
	bool doDeallocateSelf = mDoDeallocateSelf;
	NvParameterized::Traits* traits = mParameterizedTraits;
	int32_t* refCount = mRefCount;
	void* buf = mBuffer;

	this->~EmitterDebugRenderParams_0p0();

	NvParameters::destroy(this, traits, doDeallocateSelf, refCount, buf);
}

const NvParameterized::DefinitionImpl* EmitterDebugRenderParams_0p0::getParameterDefinitionTree(void)
{
	if (!mBuiltFlag) // Double-checked lock
	{
		NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

const NvParameterized::DefinitionImpl* EmitterDebugRenderParams_0p0::getParameterDefinitionTree(void) const
{
	EmitterDebugRenderParams_0p0* tmpParam = const_cast<EmitterDebugRenderParams_0p0*>(this);

	if (!mBuiltFlag) // Double-checked lock
	{
		NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			tmpParam->buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

NvParameterized::ErrorType EmitterDebugRenderParams_0p0::getParameterHandle(const char* long_name, Handle& handle) const
{
	ErrorType Ret = NvParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

NvParameterized::ErrorType EmitterDebugRenderParams_0p0::getParameterHandle(const char* long_name, Handle& handle)
{
	ErrorType Ret = NvParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

void EmitterDebugRenderParams_0p0::getVarPtr(const Handle& handle, void*& ptr, size_t& offset) const
{
	ptr = getVarPtrHelper(&ParamLookupTable[0], const_cast<EmitterDebugRenderParams_0p0::ParametersStruct*>(&parameters()), handle, offset);
}


/* Dynamic Handle Indices */

void EmitterDebugRenderParams_0p0::freeParameterDefinitionTable(NvParameterized::Traits* traits)
{
	if (!traits)
	{
		return;
	}

	if (!mBuiltFlag) // Double-checked lock
	{
		return;
	}

	NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);

	if (!mBuiltFlag)
	{
		return;
	}

	for (uint32_t i = 0; i < NumParamDefs; ++i)
	{
		ParamDefTable[i].~DefinitionImpl();
	}

	traits->free(ParamDefTable);

	mBuiltFlag = false;
}

#define PDEF_PTR(index) (&ParamDefTable[index])

void EmitterDebugRenderParams_0p0::buildTree(void)
{

	uint32_t allocSize = sizeof(NvParameterized::DefinitionImpl) * NumParamDefs;
	ParamDefTable = (NvParameterized::DefinitionImpl*)(mParameterizedTraits->alloc(allocSize));
	memset(ParamDefTable, 0, allocSize);

	for (uint32_t i = 0; i < NumParamDefs; ++i)
	{
		NV_PARAM_PLACEMENT_NEW(ParamDefTable + i, NvParameterized::DefinitionImpl)(*mParameterizedTraits);
	}

	// Initialize DefinitionImpl node: nodeIndex=0, longName=""
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[0];
		ParamDef->init("", TYPE_STRUCT, "STRUCT", true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "This class contains debug rendering parameters for the emitter module.", true);
		ParamDefTable[0].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=1, longName="apexEmitterParameters"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[1];
		ParamDef->init("apexEmitterParameters", TYPE_STRUCT, "ApexEmitterParameters", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=2, longName="apexEmitterParameters.VISUALIZE_APEX_EMITTER_ACTOR"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[2];
		ParamDef->init("VISUALIZE_APEX_EMITTER_ACTOR", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Enables/Disables visualization of all emitter actors. This parameter also switches on visualization of emitter's shape (each green grid encompasses emitter).", true);
		ParamDefTable[2].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=3, longName="apexEmitterParameters.VISUALIZE_TOTAL_INJECTED_AABB"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[3];
		ParamDef->init("VISUALIZE_TOTAL_INJECTED_AABB", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Draws red box which represents AABB boundary. All new particles are injected inside it.", true);
		ParamDefTable[3].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=4, longName="apexEmitterParameters.VISUALIZE_APEX_EMITTER_ACTOR_POSE"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[4];
		ParamDef->init("VISUALIZE_APEX_EMITTER_ACTOR_POSE", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "For visualizing emitter's position. Draws arrows which represent axes. Blue arrow stands for Z axis, green - for Y and red - X. ", true);
		ParamDefTable[4].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=5, longName="apexEmitterParameters.THRESHOLD_DISTANCE_APEX_EMITTER_ACTOR_POSE"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[5];
		ParamDef->init("THRESHOLD_DISTANCE_APEX_EMITTER_ACTOR_POSE", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Defines maximum distance, from which actor's position's visualization could be seen.", true);
		ParamDefTable[5].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=6, longName="apexEmitterParameters.VISUALIZE_APEX_EMITTER_ACTOR_NAME"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[6];
		ParamDef->init("VISUALIZE_APEX_EMITTER_ACTOR_NAME", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Draws the emitter's asset's name next to the emitter.", true);
		ParamDefTable[6].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=7, longName="apexEmitterParameters.THRESHOLD_DISTANCE_APEX_EMITTER_ACTOR_NAME"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[7];
		ParamDef->init("THRESHOLD_DISTANCE_APEX_EMITTER_ACTOR_NAME", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Defines maximum distance, from which actor name's visualization could be seen.", true);
		ParamDefTable[7].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=8, longName="groundEmitterParameters"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[8];
		ParamDef->init("groundEmitterParameters", TYPE_STRUCT, "GroundEmitterParameters", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=9, longName="groundEmitterParameters.VISUALIZE_GROUND_EMITTER_ACTOR"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[9];
		ParamDef->init("VISUALIZE_GROUND_EMITTER_ACTOR", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Enables/Disables visualization of all ground emitter actors", true);
		ParamDefTable[9].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=10, longName="groundEmitterParameters.VISUALIZE_GROUND_EMITTER_SPHERE"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[10];
		ParamDef->init("VISUALIZE_GROUND_EMITTER_SPHERE", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Draws green sphere which bounds ground emitter. ", true);
		ParamDefTable[10].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=11, longName="groundEmitterParameters.VISUALIZE_GROUND_EMITTER_GRID"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[11];
		ParamDef->init("VISUALIZE_GROUND_EMITTER_GRID", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Draws yellow grid which bounds ground emitter. ", true);
		ParamDefTable[11].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=12, longName="groundEmitterParameters.VISUALIZE_GROUND_EMITTER_RAYCAST"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[12];
		ParamDef->init("VISUALIZE_GROUND_EMITTER_RAYCAST", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Draws vertical green lines where new particles are generated. ", true);
		ParamDefTable[12].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=13, longName="groundEmitterParameters.VISUALIZE_GROUND_EMITTER_ACTOR_POSE"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[13];
		ParamDef->init("VISUALIZE_GROUND_EMITTER_ACTOR_POSE", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "For visualizing emitter's position. Draws arrows which represent axes. Blue arrow stands for Z axis, green - for Y and red - X. ", true);
		ParamDefTable[13].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=14, longName="groundEmitterParameters.VISUALIZE_GROUND_EMITTER_ACTOR_NAME"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[14];
		ParamDef->init("VISUALIZE_GROUND_EMITTER_ACTOR_NAME", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Draws the emitter's asset's name next to the emitter.", true);
		ParamDefTable[14].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=15, longName="impactEmitterParameters"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[15];
		ParamDef->init("impactEmitterParameters", TYPE_STRUCT, "ImpactEmitterParameters", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=16, longName="impactEmitterParameters.VISUALIZE_IMPACT_EMITTER_ACTOR"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[16];
		ParamDef->init("VISUALIZE_IMPACT_EMITTER_ACTOR", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Enables/Disables visualization of all impact emitter actors", true);
		ParamDefTable[16].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=17, longName="impactEmitterParameters.VISUALIZE_IMPACT_EMITTER_RAYCAST"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[17];
		ParamDef->init("VISUALIZE_IMPACT_EMITTER_RAYCAST", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Draws vertical line on the point of impact. ", true);
		ParamDefTable[17].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=18, longName="impactEmitterParameters.VISUALIZE_IMPACT_EMITTER_ACTOR_NAME"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[18];
		ParamDef->init("VISUALIZE_IMPACT_EMITTER_ACTOR_NAME", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Draws the emitter's asset's name next to the emitter.", true);
		ParamDefTable[18].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=19, longName="impactEmitterParameters.THRESHOLD_DISTANCE_IMPACT_EMITTER_ACTOR_NAME"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[19];
		ParamDef->init("THRESHOLD_DISTANCE_IMPACT_EMITTER_ACTOR_NAME", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Defines maximum distance, from which actor's names's visualization could be seen.", true);
		ParamDefTable[19].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// SetChildren for: nodeIndex=0, longName=""
	{
		static Definition* Children[3];
		Children[0] = PDEF_PTR(1);
		Children[1] = PDEF_PTR(8);
		Children[2] = PDEF_PTR(15);

		ParamDefTable[0].setChildren(Children, 3);
	}

	// SetChildren for: nodeIndex=1, longName="apexEmitterParameters"
	{
		static Definition* Children[6];
		Children[0] = PDEF_PTR(2);
		Children[1] = PDEF_PTR(3);
		Children[2] = PDEF_PTR(4);
		Children[3] = PDEF_PTR(5);
		Children[4] = PDEF_PTR(6);
		Children[5] = PDEF_PTR(7);

		ParamDefTable[1].setChildren(Children, 6);
	}

	// SetChildren for: nodeIndex=8, longName="groundEmitterParameters"
	{
		static Definition* Children[6];
		Children[0] = PDEF_PTR(9);
		Children[1] = PDEF_PTR(10);
		Children[2] = PDEF_PTR(11);
		Children[3] = PDEF_PTR(12);
		Children[4] = PDEF_PTR(13);
		Children[5] = PDEF_PTR(14);

		ParamDefTable[8].setChildren(Children, 6);
	}

	// SetChildren for: nodeIndex=15, longName="impactEmitterParameters"
	{
		static Definition* Children[4];
		Children[0] = PDEF_PTR(16);
		Children[1] = PDEF_PTR(17);
		Children[2] = PDEF_PTR(18);
		Children[3] = PDEF_PTR(19);

		ParamDefTable[15].setChildren(Children, 4);
	}

	mBuiltFlag = true;

}
void EmitterDebugRenderParams_0p0::initStrings(void)
{
}

void EmitterDebugRenderParams_0p0::initDynamicArrays(void)
{
}

void EmitterDebugRenderParams_0p0::initDefaults(void)
{

	freeStrings();
	freeReferences();
	freeDynamicArrays();
	apexEmitterParameters.VISUALIZE_APEX_EMITTER_ACTOR = bool(false);
	apexEmitterParameters.VISUALIZE_TOTAL_INJECTED_AABB = bool(false);
	apexEmitterParameters.VISUALIZE_APEX_EMITTER_ACTOR_POSE = bool(true);
	apexEmitterParameters.THRESHOLD_DISTANCE_APEX_EMITTER_ACTOR_POSE = float(3.402823466e+038);
	apexEmitterParameters.VISUALIZE_APEX_EMITTER_ACTOR_NAME = bool(true);
	apexEmitterParameters.THRESHOLD_DISTANCE_APEX_EMITTER_ACTOR_NAME = float(3.402823466e+038);
	groundEmitterParameters.VISUALIZE_GROUND_EMITTER_ACTOR = bool(true);
	groundEmitterParameters.VISUALIZE_GROUND_EMITTER_SPHERE = bool(false);
	groundEmitterParameters.VISUALIZE_GROUND_EMITTER_GRID = bool(false);
	groundEmitterParameters.VISUALIZE_GROUND_EMITTER_RAYCAST = bool(false);
	groundEmitterParameters.VISUALIZE_GROUND_EMITTER_ACTOR_POSE = bool(false);
	groundEmitterParameters.VISUALIZE_GROUND_EMITTER_ACTOR_NAME = bool(false);
	impactEmitterParameters.VISUALIZE_IMPACT_EMITTER_ACTOR = bool(false);
	impactEmitterParameters.VISUALIZE_IMPACT_EMITTER_RAYCAST = bool(true);
	impactEmitterParameters.VISUALIZE_IMPACT_EMITTER_ACTOR_NAME = bool(true);
	impactEmitterParameters.THRESHOLD_DISTANCE_IMPACT_EMITTER_ACTOR_NAME = float(3.402823466e+038);

	initDynamicArrays();
	initStrings();
	initReferences();
}

void EmitterDebugRenderParams_0p0::initReferences(void)
{
}

void EmitterDebugRenderParams_0p0::freeDynamicArrays(void)
{
}

void EmitterDebugRenderParams_0p0::freeStrings(void)
{
}

void EmitterDebugRenderParams_0p0::freeReferences(void)
{
}

} // namespace parameterized
} // namespace nvidia

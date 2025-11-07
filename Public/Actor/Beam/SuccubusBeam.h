// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Beam/BeamBase.h"
#include "SuccubusBeam.generated.h"

/**
 * 
 */
UCLASS()
class GFANTASY_API ASuccubusBeam : public ABeamBase
{
	GENERATED_BODY()
	
	protected:
	virtual void SetStartAndEndPoint() override;
	
	
};

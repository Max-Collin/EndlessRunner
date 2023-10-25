// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameManager.generated.h"



class AEndlessBlock;
/**
 * 
 */
UCLASS()
class WORKSHOP4_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

private:
	 void BeginPlay() ;
	
};

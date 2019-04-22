// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Socket.generated.h"

UENUM(BlueprintType)
enum class ESocketState : uint8
{
	XMark, OMark, Empty //3 состояния поля - Х,0,Пусто
};
UCLASS()
class TICTACTOE_API ASocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASocket();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Props")
	ESocketState State = ESocketState::Empty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Props")
	int32 index;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

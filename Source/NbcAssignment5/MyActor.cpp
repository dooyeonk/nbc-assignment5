// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"

#include "Engine/Engine.h"

// Sets default values
AMyActor::AMyActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    MoveCount = 0;
    StartLocation = FVector(0, 50, 0);
    TotalMoveCount = 10;
    EventCount = 0;
    TotalDistance = 0;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
    Super::BeginPlay();

    SetActorLocation(StartLocation);
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyActor::RandomMoveAndTurn, 0.5f, true);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyActor::Move(const FVector& NewLocation) {
    TotalDistance += FVector::Distance(GetActorLocation(), NewLocation);
    SetActorLocation(NewLocation);
}

void AMyActor::Turn(const FRotator& NewRotation) {
    SetActorRotation(NewRotation);
}

void AMyActor::RandomMoveAndTurn() {
    if (MoveCount++ < 10) {
        FVector RandomLocation = FVector(
            FMath::RandRange(-300.f, 300.f),
            FMath::RandRange(-300.f, 300.f),
            FMath::RandRange(0.f, 300.f)
        );
        FRotator RandomRotation = FRotator(
            FMath::RandRange(-300.f, 300.f),
            FMath::RandRange(-300.f, 300.f),
            FMath::RandRange(-300.f, 300.f)
        );

        Move(RandomLocation);
        Turn(RandomRotation);

        SCREENLOG(FColor::Blue, TEXT("move count: %d"), MoveCount);
        SCREENLOG(FColor::Blue, TEXT("location: %s"), *RandomLocation.ToString());
        //SCREENLOG(FColor::Blue, TEXT("rotation: %s"), *NewRotation.ToString());

        if (EventTriggered()) {
            SCREENLOG(FColor::Green, TEXT("EVENT TRIGGERED"));
        }
    }
    else {
        SCREENLOG(FColor::Yellow, TEXT("total distance: %.2f, event triggered count: %d"), TotalDistance, EventCount);
        GetWorldTimerManager().ClearTimer(TimerHandle);
    }
}

bool AMyActor::EventTriggered() {
    float RandomValue = FMath::FRand();
    if (RandomValue >= 0.5f) {
        EventCount++;
        return true;
    }

    return false;
}

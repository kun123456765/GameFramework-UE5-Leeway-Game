//--------------------
// kun 2025.01.31
//--------------------

#include "LWCharacterUserWidget.h"
#include "Leeway/Actor/Character/BaseCharacter.h"

void ULWCharacterUserWidget::SetOwningComponent(UBaseWidgetComponent* WidgetComponent)
{
    Super::SetOwningComponent(WidgetComponent);
    BaseCharacter = Cast<ABaseCharacter>(WidgetComponent->GetOwner());
}
